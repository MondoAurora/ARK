package dust.mod;

public class DustJdbc implements DustComponents.DustAgent, ModuleTokens {

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        switch (action) {
        case INIT:
                      
            TOKEN_UTILS.setMemberMeta(GuardRefAccountId, MiND_IdeaTagValRef, MiND_IdeaTagCollOne);
            TOKEN_UTILS.setMemberMeta(GuardRefAccountPass, MiND_IdeaTagValRef, MiND_IdeaTagCollOne);
            TOKEN_UTILS.setMemberMeta(JdbcRefConnectorDriver, MiND_IdeaTagValRef, MiND_IdeaTagCollOne);
            TOKEN_UTILS.setMemberMeta(JdbcRefConnectorPath, MiND_IdeaTagValRef, MiND_IdeaTagCollOne);
            TOKEN_UTILS.setMemberMeta(TextRefIdentifiedId, MiND_IdeaTagValRef, MiND_IdeaTagCollOne);
            
            TOKEN_UTILS.setTextMember(tray.entity, MiND_NativeRefModuleObjects.getEntity(), 
                    JdbcTypeConnector.getEntity(), "dust.mod.jdbc.JdbcAgent");
            break;
        default:
            break;
        }
        return null;
    }
}


