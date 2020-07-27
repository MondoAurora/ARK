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
        // variants.put(VAR_ENTITY_PRIMARY_TYPE, new RuntimeDataVariant(primaryType,
        // VAL_REF));
        // variants.put(VAR_ENTITY_STORE_ID, new RuntimeDataVariant(id, VAL_INTEGER));
    }

    @SuppressWarnings("unchecked")
   @Override
    public <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray) {

        RuntimeDataVariant v = variants.get(tray.token);
        Object ret = null;
        RuntimeDataToken t;

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
                t = RuntimeAgent.getToken(tray.token);
                v = new RuntimeDataVariant(t, tray.value, tray.key);
                break;
            }
        } else {
            ret = v.access(cmd, tray);
            if ( (DustDialogCmd.DEL == cmd) && !v.isValid() ) {
                variants.remove(tray.token);
            }
        }

        return (RetType) ret;
    }

    @Override
    public DustResultType visit(DustAgent visitor, DustDialogTray tray) throws Exception {
        DustResultType rt = DustResultType.REJECT;

        if (CONST_NULL != tray.token) {
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
