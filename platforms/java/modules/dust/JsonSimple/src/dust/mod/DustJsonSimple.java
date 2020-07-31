package dust.mod;

public class DustJsonSimple implements DustComponents.DustAgent, ModuleTokens {

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        switch (action) {
        case INIT:
            TOKEN_UTILS.setTextMember(tray.entity, MiND_NativeRefModuleObjects.getEntity(), JsonTypeConnector.getEntity(), "dust.mod.jsonsimple.JsonSimpleAgent");
            break;
        default:
            break;
        }
        return null;
    }

}
