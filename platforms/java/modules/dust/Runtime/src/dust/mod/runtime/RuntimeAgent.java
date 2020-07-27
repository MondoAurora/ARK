package dust.mod.runtime;

import java.util.HashMap;
import java.util.Map;

import dust.mod.DustComponents;
import dust.mod.runtime.data.RuntimeDataComponents.CollType;
import dust.mod.runtime.data.RuntimeDataComponents.ValType;
import dust.mod.runtime.data.RuntimeDataStore;
import dust.mod.runtime.data.RuntimeDataToken;

public class RuntimeAgent implements DustComponents.DustDialogAPI, DustComponents.DustAgent, RuntimeComponents {
    private static RuntimeAgent THE_AGENT;
    
    NativeApp app = null;
    private final Map<Integer, RuntimeDataToken> tokens = new HashMap<>();

    RuntimeDataStore testStore = new RuntimeDataStore();
    
    public RuntimeAgent() {
        tokens.put(-2, new RuntimeDataToken(0, 0, ValType.INTEGER, CollType.SINGLE));
    }
    
    @Override
    public <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray) {
        return testStore.access(cmd, tray);
    }

    @Override
    public DustResultType visit(DustAgent visitor, DustDialogTray tray) throws Exception {
        return testStore.visit(visitor, tray);
    }

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        return DustResultType.ACCEPT;
    }
    
    public RuntimeDataToken getToken_(int entity) {
        RuntimeDataToken rt = tokens.get(entity);
        
        return rt;
    }
    
    void test() {
        DustDialogTray tray = new DustDialogTray();
        
        tray.token = -3;
        
        tray.entity = THE_AGENT.access(DustDialogCmd.ADD, tray);
        
        tray.token = -2;
        tray.value = 42;
        
        THE_AGENT.access(DustDialogCmd.SET, tray);
    }
    
    public static RuntimeDataToken getToken(int entity) {
        return THE_AGENT.getToken_(entity);
    }
    
    public static DustDialogAPI createRuntime(NativeApp app) {
        THE_AGENT = new RuntimeAgent();
        
        THE_AGENT.app = app;

        THE_AGENT.test();
        
        return THE_AGENT;
    }
}
