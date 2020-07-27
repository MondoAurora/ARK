package dust.mod.jsonsimple;

import org.json.simple.JSONValue;

import dust.mod.DustComponents;

public class JsonSimpleAgent implements DustComponents, DustComponents.DustAgent {

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        Object ob = JSONValue.parse("{\"test\":true}");
        System.out.println("Kukucs... " + ob);
        return DustResultType.ACCEPT_PASS;
    }
}
