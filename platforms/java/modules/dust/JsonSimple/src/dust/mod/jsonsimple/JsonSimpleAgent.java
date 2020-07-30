package dust.mod.jsonsimple;

import org.json.simple.JSONValue;

import dust.mod.Dust;
import dust.mod.DustComponents;

public class JsonSimpleAgent implements JsonSimpleComponents, DustComponents.DustAgent {

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        Object ob = JSONValue.parse("{\"test\":true}");
        System.out.println("Kukucs... " + ob);

        DustDialogTray t = new DustDialogTray();

        t.entity = -3;
        t.setToken(MiND_ModelIntEntityStoreId);
        t.value = 0;

        int ret = Dust.access(DustDialogCmd.GET, t);
        System.out.println("The answer is... " + ret);
        
        t.setToken(MiND_ModelNativeEntityContent);
        t.key = TextTypeStatementImmutable.getEntity();
        t.value = "?";

        String msg = Dust.access(DustDialogCmd.GET, t);
        System.out.println("The message is... " + msg);
        
        return DustResultType.ACCEPT_PASS;
    }
}
