package dust.mod.jdbc;

import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Map;

import dust.mod.DustComponents;
import dust.mod.DustUtils;
import dust.mod.ModuleTokens;

public class JdbcAgent implements ModuleTokens, DustComponents.DustAgent {
    Map<DustToken, String> params;
    Connection conn = null;
    DatabaseMetaData dbMetaData;

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        switch (action) {
        case BEGIN:
            params = TOKEN_UTILS.getTextParams(params, tray.entity, JdbcRefConnectorDriver, JdbcRefConnectorPath, GuardRefAccountId,
                    GuardRefAccountPass, TextRefIdentifiedId);

            return DustResultType.ACCEPT_PASS;
        case PROCESS:
            optCreateConn();
            String query = "select * from mind_core_entity";

            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);

            JdbcUtils.dumpResultSet(rs);
            
            return DustResultType.ACCEPT_PASS;
        case END:
            releaseConn(conn, null);
            return DustResultType.ACCEPT_PASS;
            
        default:
            return DustResultType.ACCEPT_PASS;
        }
    }

    private void optCreateConn() throws Exception {
        if ((null == conn) || conn.isClosed()) {
            System.out.println("Connecting to database...");

            try {
                Class.forName(params.get(JdbcRefConnectorDriver));

                String dbName = params.get(TextRefIdentifiedId);
                String dbUrl = params.get(JdbcRefConnectorPath);
                if (!DustUtils.isEmpty(dbName) && !dbUrl.endsWith(dbName)) {
                    dbUrl += "/" + dbName;
                }
                conn = DriverManager.getConnection(dbUrl, params.get(GuardRefAccountId), params.get(GuardRefAccountPass));

                JdbcUtils.addConn(conn);

                dbMetaData = conn.getMetaData();

                System.out.println("Connection successful.");

            } catch (Throwable e) {
                releaseConn(conn, e);
                conn = null;
                dbMetaData = null;
                DustException.throwException(e);
            }
        }
    }

    public static void releaseConn(Connection conn, Throwable cause) throws Exception {
        if (null != conn) {
            if (!conn.isClosed()) {
                if (!conn.getAutoCommit()) {
                    if (null == cause) {
                        conn.commit();
                    } else {
                        conn.rollback();
                    }
                }
                conn.close();
                System.out.println("DB connection closed.");
            }
            conn = null;
        }
    }

}
