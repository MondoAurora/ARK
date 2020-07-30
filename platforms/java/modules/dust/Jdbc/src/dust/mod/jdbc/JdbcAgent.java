package dust.mod.jdbc;

import dust.mod.DustComponents;

public class JdbcAgent implements DustComponents, DustComponents.DustAgent {
    
    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        switch (action) {
        case INIT:            
            return DustResultType.ACCEPT_PASS;
        case RELEASE:
            return DustResultType.ACCEPT_PASS;            
        default:
            return DustResultType.ACCEPT_PASS;   
        }
    }

}
