package dust.mod.runtime.data;

import dust.mod.Dust;
import dust.mod.DustComponents.DustAgent;

public class RuntimeDataTokenInfo implements RuntimeDataComponents, DustAgent {

    private int store;
    private int storeId;

    private ValType valType;
    private CollType collType;

    public RuntimeDataTokenInfo(DustToken token, ValType valType, CollType collType) {
        this.store = token.store;
        this.storeId = token.id;

        this.valType = valType;
        this.collType = collType;
    }

    public RuntimeDataTokenInfo() {
    }

    public boolean matchId(int store, int storeId) {
        return (this.store == store) && (this.storeId == storeId);
    }

    public void load(int entity) {
        DustDialogTray tray = new DustDialogTray();

        try {
            tray.entity = entity;
            tray.setToken(MiND_ModelIntEntityStoreId);
            storeId = Dust.access(DustDialogCmd.GET, tray);

            tray.setToken(MiND_ModelRefEntityTags);
            Dust.visit(new DustAgent() {
                @Override
                public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
                    if (DustAgentAction.PROCESS == action) {
                        ValType vt = ValType.fromEntity((Integer) tray.value);
                        if (null != vt) {
                            RuntimeDataTokenInfo.this.valType = vt;
                        } else {
                            CollType ct = CollType.fromEntity((Integer) tray.value);
                            if (null != ct) {
                                RuntimeDataTokenInfo.this.collType = ct;
                            }
                        }
                    }
                    return null;
                }
            }, tray);
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public ValType getValType() {
        return valType;
    }

    public CollType getCollType() {
        return collType;
    }

    public int getStore() {
        return store;
    }

    public int getStoreId() {
        return storeId;
    }

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        // TODO Auto-generated method stub
        return null;
    }

}
