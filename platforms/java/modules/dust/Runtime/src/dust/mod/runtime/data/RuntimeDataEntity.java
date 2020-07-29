package dust.mod.runtime.data;

import java.util.HashMap;
import java.util.Map;

import dust.mod.runtime.RuntimeAgent;
import dust.mod.runtime.data.RuntimeDataComponents.RuntimeData;

public class RuntimeDataEntity implements RuntimeData {
    RuntimeDataStore store;

    Map<Integer, RuntimeDataVariant> variants = new HashMap<Integer, RuntimeDataVariant>();

    public RuntimeDataEntity(RuntimeDataStore store, int primaryType, int id) {
        this.store = store;
        setVariant(MiND_ModelRefEntityPrimaryType.getEntity(), primaryType, null);
        setVariant(MiND_ModelIntEntityStoreId.getEntity(), id, null);
    }

    public void setNewVariant(int token, Object value, Integer key) {
        RuntimeDataTokenInfo t = RuntimeAgent.getToken(token);
        RuntimeDataVariant v = new RuntimeDataVariant(t, value, key);
        variants.put(token, v);            
    }

    public void setVariant(int token, Object value, Integer key) {
        RuntimeDataVariant v = variants.get(token);
        
        if ( null == v ) {
            setNewVariant(token, value, key);
        } else {
            DustDialogTray tray = new DustDialogTray();
            tray.token = token;
            tray.value = value;
            tray.key = key;
            v.access(DustDialogCmd.SET, tray);
        }
    }
    
    @SuppressWarnings("unchecked")
   @Override
    public <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray) {

        RuntimeDataVariant v = variants.get(tray.token);
        Object ret = null;

        if (null == v) {
            switch (cmd) {
            case CHK:
            case DEL:
                ret = false;
                break;
            case GET:
                ret = tray.value;
                break;
            case SET:
            case ADD:
                setNewVariant(tray.token, tray.value, tray.key);
                break;
            }
        } else {
            ret = v.access(cmd, tray);
            if ( ((DustDialogCmd.DEL == cmd) || (DustDialogCmd.SET == cmd)) && !v.isValid() ) {
                variants.remove(tray.token);
            }
        }

        return (RetType) ret;
    }

    @Override
    public DustResultType visit(DustAgent visitor, DustDialogTray tray) throws Exception {
        DustResultType rt = DustResultType.REJECT;

        if (null != tray.token) {
            RuntimeDataVariant v = variants.get(tray.token);
            if (null != v) {
                rt = v.visit(visitor, tray);
            }
        } else {
            if (!variants.isEmpty()) {
                rt = visitor.agentAction(DustAgentAction.BEGIN, tray);
                if (rt != DustResultType.REJECT) {
                    for (Map.Entry<Integer, RuntimeDataVariant> v : variants.entrySet()) {
                        tray.token = v.getKey();
                        v.getValue().visit(visitor, tray);
                    }
                }
                visitor.agentAction(DustAgentAction.END, tray);
            }
        }

        return rt;
    }
}
