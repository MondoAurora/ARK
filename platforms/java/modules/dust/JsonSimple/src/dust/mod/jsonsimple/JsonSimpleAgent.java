package dust.mod.jsonsimple;

import org.json.simple.JSONValue;

import dust.mod.DustComponents;

public class JsonSimpleAgent extends DustComponents.DustAgentDefault implements DustComponents {

    @Override
    public DustResultType agentProcess() throws Exception {
        Object ob = JSONValue.parse("{\"test\":true}");
        System.out.println("Kukucs... " + ob);
        return super.agentProcess();
    }
}
