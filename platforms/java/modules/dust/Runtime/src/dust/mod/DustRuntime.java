package dust.mod;

import dust.app.DustAppComponents.NativeApp;
import dust.gen.DustGenConsts.DustAgentAction;
import dust.gen.DustGenConsts.DustResultType;
import dust.mod.DustComponents.DustDialogTray;
import dust.mod.runtime.RuntimeAgent;

public class DustRuntime implements DustComponents.DustAgent {

    public static void bootRuntime(NativeApp app) {
        RuntimeAgent.createRuntime(app);
    }

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        return null;
    }

}


