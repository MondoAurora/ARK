package dust.test01.app01;

import dust.app.DustApp;
import dust.app.DustAppComponents;
import dust.mod.Dust;
import dust.mod.DustUtils;

public class DustAppTest01App01 implements DustAppComponents, AppBootTokens {
    private static DustUtils.TokenUtils TOKEN_UTILS;
//    static void setMember(DustDialogTray t, DustToken token, DustToken tType, DustToken tColl) {
//        t.entity = token.getEntity();
//        t.setToken(MiND_ModelRefEntityTags);
//
//        t.value = tType.getEntity();
//        Dust.access(DustDialogCmd.ADD, t);
//        t.value = tColl.getEntity();
//        Dust.access(DustDialogCmd.ADD, t);
//    }
//
//    public static void setParamText(DustDialogTray tTarget, DustDialogTray tMember, DustToken token, String val) {
//        setMember(tMember, token, MiND_IdeaTagValRef, MiND_IdeaTagCollOne);
//
//        tMember.entity = null;
//        tMember.setToken(TextTypeStatementImmutable);
//        Integer eParam = Dust.access(DustDialogCmd.ADD, tMember);
//
//        tMember.entity = eParam;
//        tMember.value = val;
//        Dust.access(DustDialogCmd.SET, tMember);
//
//        tTarget.setToken(token);
//        tTarget.value = eParam;
//        Dust.access(DustDialogCmd.SET, tTarget);
//    }

    public static int setupMain(DustApp app, String[] args) {
        DustDialogTray tConn = new DustDialogTray();

        tConn.setToken(JdbcTypeConnector);
        Integer eConn = Dust.access(DustDialogCmd.ADD, tConn);
        tConn.entity = eConn;

//        DustDialogTray tMember = new DustDialogTray();
        
        TOKEN_UTILS.setTextMember(eConn, GuardRefAccountId.getEntity(), 0, "arkUser");
        TOKEN_UTILS.setTextMember(eConn, GuardRefAccountPass.getEntity(), 0, "ark01");
        TOKEN_UTILS.setTextMember(eConn, JdbcRefConnectorDriver.getEntity(), 0, "com.mysql.jdbc.Driver");
        TOKEN_UTILS.setTextMember(eConn, JdbcRefConnectorPath.getEntity(), 0, "jdbc:mysql://localhost:3306/ark01");

//        setParamText(tConn, tMember, GuardRefAccountId, "arkUser");
//        setParamText(tConn, tMember, GuardRefAccountPass, "ark01");
//        setParamText(tConn, tMember, JdbcRefConnectorDriver, "com.mysql.jdbc.Driver");
//        setParamText(tConn, tMember, JdbcRefConnectorPath, "jdbc:mysql://localhost:3306/ark01");
        
        return eConn;
    }

    public static void main(String[] args) {
        System.out.println("Hello world 4!");

        try {
            DustApp app = new DustApp(APP_TOKENS, "DustRuntime", new int[] { 0 });
            
            app.addModule("DustJsonSimple", new int[] { 0 }, "json/json-simple-1.1.1.jar");
            app.addModule("DustJdbc", new int[] { 0 }, "jdbc/mysql-connector-java-8.0.18.jar");

            TOKEN_UTILS = new DustUtils.TokenUtils(TextTypeStatementImmutable, MiND_ModelNativeEntityContent, MiND_ModelRefEntityTags);

            int db = setupMain(app, args);

            DustDialogTray tray = new DustDialogTray();
            tray.setToken(JsonTypeConnector);            
            int json = Dust.access(DustDialogCmd.ADD, tray);
            
            tray.entity = json;
            tray.setToken(MiND_ModelNativeEntityContent);
            
            DustAgent js = Dust.access(DustDialogCmd.GET, tray);
            
            js.agentAction(DustAgentAction.PROCESS, null);
            
            
            tray.entity = db;
            tray.key = null;
            tray.setToken(MiND_ModelNativeEntityContent);
            
            DustAgent dbConn = Dust.access(DustDialogCmd.GET, tray);
            
            dbConn.agentAction(DustAgentAction.BEGIN, tray);
            dbConn.agentAction(DustAgentAction.PROCESS, tray);
            dbConn.agentAction(DustAgentAction.END, tray);

        } catch (Exception e) {
            DustException.throwException(e);
        }
    }
}
