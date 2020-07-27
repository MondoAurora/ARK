package dust.mod.jsonsimple;

import org.json.simple.JSONValue;

import dust.mod.Dust;
import dust.mod.DustComponents;

public class JsonSimpleAgent implements DustComponents, DustComponents.DustAgent {

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        Object ob = JSONValue.parse("{\"test\":true}");
        System.out.println("Kukucs... " + ob);

        DustDialogTray t = new DustDialogTray();

        t.entity = 1;
        t.token = -2;
        t.value = 0;

        int ret = Dust.access(DustDialogCmd.GET, t);
        System.out.println("The answer is... " + ret);
        
        return DustResultType.ACCEPT_PASS;
    }
}
