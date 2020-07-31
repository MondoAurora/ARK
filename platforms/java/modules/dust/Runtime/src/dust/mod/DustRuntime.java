package dust.mod;

import dust.app.DustAppComponents.NativeApp;
import dust.mod.DustComponents.DustAgentAction;
import dust.mod.DustComponents.DustDialogTray;
import dust.mod.DustComponents.DustResultType;
import dust.mod.runtime.RuntimeAgent;

public class DustRuntime implements DustComponents.DustAgent {

    public static void bootRuntime(NativeApp app) {
        RuntimeAgent.createRuntime(app);
    }

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        // TODO Auto-generated method stub
        return null;
    }

}
