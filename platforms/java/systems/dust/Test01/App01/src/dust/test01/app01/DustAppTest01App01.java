package dust.test01.app01;

import dust.app.DustApp;
import dust.app.DustAppComponents;
import dust.mod.Dust;

public class DustAppTest01App01 implements DustAppComponents, AppBootTokens {

    static void setMember(DustDialogTray t, DustToken token, DustToken tType, DustToken tColl) {
        t.entity = token.getEntity();
        t.setToken(MiND_ModelRefEntityTags);

        t.value = tType.getEntity();
        Dust.access(DustDialogCmd.ADD, t);
        t.value = tColl.getEntity();
        Dust.access(DustDialogCmd.ADD, t);
    }

    public static void setParamText(DustDialogTray tTarget, DustDialogTray tMember, DustToken token, String val) {
        setMember(tMember, token, MiND_IdeaTagValRef, MiND_IdeaTagCollOne);

        tMember.entity = null;
        tMember.setToken(TextTypeStatementImmutable);
        Integer eParam = Dust.access(DustDialogCmd.ADD, tMember);

        tMember.entity = eParam;
        tMember.value = val;
        Dust.access(DustDialogCmd.SET, tMember);

        tTarget.setToken(token);
        tTarget.value = eParam;
        Dust.access(DustDialogCmd.SET, tTarget);
    }

    public static void setupMain(DustApp app, String[] args) {
        DustDialogTray tConn = new DustDialogTray();

        tConn.setToken(JdbcTypeConnector);
        Integer eConn = Dust.access(DustDialogCmd.ADD, tConn);
        tConn.entity = eConn;

        DustDialogTray tMember = new DustDialogTray();

        setParamText(tConn, tMember, GuardRefAccountId, "arkUser");
        setParamText(tConn, tMember, GuardRefAccountPass, "ark01");
        setParamText(tConn, tMember, JdbcRefConnectorDriver, "com.mysql.jdbc.Driver");
        setParamText(tConn, tMember, JdbcRefConnectorPath, "jdbc:mysql://localhost:3306/ark01");
    }

    public static void main(String[] args) {
        int eJS = -1;

        System.out.println("Hello world 3!");

        try {
            DustApp app = new DustApp("dustRuntime", new int[] { 0 });

            NativeModule m;

            m = app.addModule("dustJsonSimple", new int[] { 0 }, "json/json-simple-1.1.1.jar");
            m.assignClass(eJS, "dust.mod.jsonsimple.JsonSimpleAgent");

            
            setupMain(app, args);


            DustAgent js = app.createNative(eJS);

            js.agentAction(DustAgentAction.PROCESS, null);
        } catch (Exception e) {
            DustException.throwException(e);
        }
    }
}
