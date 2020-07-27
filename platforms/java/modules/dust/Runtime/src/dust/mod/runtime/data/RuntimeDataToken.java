package dust.mod.runtime.data;

import dust.mod.DustComponents.DustAgent;

public class RuntimeDataToken implements RuntimeDataComponents, DustAgent {
    
    private int store;
    private int storeId;
    
    private ValType valType;
    private CollType collType;
    
        
    public RuntimeDataToken(int store, int storeId, ValType valType, CollType collType) {
        this.store = store;
        this.storeId = storeId;
        this.valType = valType;
        this.collType = collType;
    }
    
    public RuntimeDataToken() {
    }

    public boolean matchId(int store, int storeId) {
        return (this.store == store) && (this.storeId == storeId);
    }

    public void load(DustDialogTray tray) {
    }

    public ValType getValType() {
        return valType;
    }
    
    public CollType getCollType() {
        return collType;
    }

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        // TODO Auto-generated method stub
        return null;
    }

    
}
