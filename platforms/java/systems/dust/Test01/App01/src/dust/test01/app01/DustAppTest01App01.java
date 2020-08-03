package dust.test01.app01;

import dust.app.DustApp;
import dust.app.DustAppComponents;
import dust.mod.Dust;
import dust.mod.DustUtils;

public class DustAppTest01App01 implements DustAppComponents, AppBootTokens {
    private static DustUtils.TokenUtils TOKEN_UTILS;

    public static void main(String[] args) {
        System.out.println("Hello world - Jdbc demo");

        try {            
            // Load modules
            DustApp app = new DustApp(APP_TOKENS, "DustRuntime", new int[] { 0 });
            app.addModule("DustJdbc", new int[] { 0 }, "jdbc/mysql-connector-java-8.0.18.jar");

            // Create main test entity
            DustDialogTray tray = new DustDialogTray();

            tray.setToken(JdbcTypeConnector);
            Integer db = Dust.access(DustDialogCmd.ADD, tray);
            
            // Set up parameters
            TOKEN_UTILS = new DustUtils.TokenUtils(TextTypeStatementImmutable, 
                    MiND_ModelNativeEntityContent, MiND_ModelRefEntityTags);

            tray.entity = db;
            TOKEN_UTILS.setTextMember(db, GuardRefAccountId.getEntity(), 0, "arkUser");
            TOKEN_UTILS.setTextMember(db, GuardRefAccountPass.getEntity(), 0, "ark01");
            TOKEN_UTILS.setTextMember(db, JdbcRefConnectorDriver.getEntity(), 0, 
                    "com.mysql.cj.jdbc.Driver");
            TOKEN_UTILS.setTextMember(db, JdbcRefConnectorPath.getEntity(), 0, 
                    "jdbc:mysql://localhost:3306/ark01");
            
            // Have the Jdbc module create the Agent (only for testing!)
            tray.key = null;
            tray.setToken(MiND_ModelNativeEntityContent);
            DustAgent dbConn = Dust.access(DustDialogCmd.GET, tray);
            
            // Run the test 
            dbConn.agentAction(DustAgentAction.BEGIN, tray);
            dbConn.agentAction(DustAgentAction.PROCESS, tray);
            dbConn.agentAction(DustAgentAction.END, tray);

        } catch (Exception e) {
            DustException.throwException(e);
        }
    }
}


