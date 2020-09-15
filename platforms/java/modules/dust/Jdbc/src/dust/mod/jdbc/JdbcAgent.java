package dust.mod.jdbc;

import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Map;

import dust.gen.DustGenLog;
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
            params = TOKEN_UTILS.getTextParams(params, tray.entity, JdbcRefConnectorDriver, JdbcRefConnectorPath, 
                    GuardRefAccountId, GuardRefAccountPass, TextRefIdentifiedId);

            return DustResultType.ACCEPT_PASS;
        case PROCESS:
            optCreateConn();
            String query = "select * from mind_core_entity";

            DustGenLog.log(DustEventLevel.TRACE, "Running SQL command", query);
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
            String dbName = params.get(TextRefIdentifiedId);
            String dbUrl = params.get(JdbcRefConnectorPath);
            if (!DustUtils.isEmpty(dbName) && !dbUrl.endsWith(dbName)) {
                dbUrl += "/" + dbName;
            }

            DustGenLog.log(DustEventLevel.TRACE, "Connecting to database...", dbUrl);

            try {
                Class.forName(params.get(JdbcRefConnectorDriver));

                conn = DriverManager.getConnection(dbUrl, params.get(GuardRefAccountId), params.get(GuardRefAccountPass));

                JdbcUtils.addConn(conn);

                dbMetaData = conn.getMetaData();

                DustGenLog.log(DustEventLevel.TRACE, "Connection successful.");

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
                DustGenLog.log(DustEventLevel.TRACE, "DB connection closed.");
            }
            conn = null;
        }
    }

}
