package dust.mod.runtime;

import java.util.HashMap;
import java.util.Map;

import dust.app.DustAppComponents;
import dust.mod.DustComponents;
import dust.mod.runtime.data.RuntimeDataToken;

public class RuntimeAgent implements DustComponents.DustDialogAPI, DustComponents.DustAgent, DustAppComponents.NativeRuntime, RuntimeComponents {
    private static RuntimeAgent THE_AGENT;
    
    NativeApp app = null;
    private final Map<Integer, RuntimeDataToken> tokens = new HashMap<>();

    
    @Override
    public <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public DustResultType visit(DustAgent visitor, DustDialogTray tray) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public void setApp(NativeApp app) {
        if ( null == this.app ) {
            this.app = app;
        } else {
            DustException.throwException(null, "Duplicate runtime initialization");
        }
    }

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        return DustResultType.ACCEPT;
    }
    
    public RuntimeDataToken getToken_(int entity) {
        RuntimeDataToken rt = tokens.get(entity);
        
        return rt;
    }
    
    public static RuntimeDataToken getToken(int entity) {
        return THE_AGENT.getToken_(entity);
    }
}
