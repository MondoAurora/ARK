package dust.mod.runtime.data;

import java.util.HashMap;
import java.util.Map;

import dust.mod.DustUtils;
import dust.mod.runtime.data.RuntimeDataComponents.RuntimeData;

public class RuntimeDataStore implements RuntimeData {
    RuntimeDataStore parent;

    int lastId = 0;

    Map<Integer, RuntimeDataEntity> entities = new HashMap<Integer, RuntimeDataEntity>();

    public RuntimeDataEntity newEntity(int primaryType) {
        return getEntity(++lastId, primaryType);
    }

    public RuntimeDataEntity getEntity(int id, int primaryType) {
        RuntimeDataEntity e = entities.get(id);
        
        if ( null == e ) {
            e = new RuntimeDataEntity(this, primaryType, id);
            put(id, e);
        }
        
        return e;
    }

    public void put(int id, RuntimeDataEntity e) {
        entities.put(id, e);
        
        if ( id > lastId ) {
            lastId = id;
        }
    }

    RuntimeDataEntity removeEntity(int id) {
        return entities.remove(id);
    }

    @SuppressWarnings("unchecked")
    @Override
    public <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray) {
        RuntimeDataEntity e = null;
        Object ret = null;

        if (null == tray.entity) {
            if ((DustDialogCmd.ADD == cmd) && (null != tray.token)) {
                e = newEntity(tray.token);
                ret = tray.entity = lastId;
            }
        } else {
            e = entities.get(tray.entity);

            if (null == tray.token) {
                switch (cmd) {
                case CHK:
                    ret = (null != e);
                    break;
                case DEL:
                    if (null != e) {
                        removeEntity(tray.entity);
                        ret = true;
                    } else {
                        ret = false;
                    }
                    break;
                case ADD:
                    break;
                case GET:
                    break;
                case SET:
                    break;
                }
            } else if (null != e) {
                ret = e.access(cmd, tray);
            }
        }

        return (RetType) ret;
    }

    @Override
    public DustResultType visit(DustAgent visitor, DustDialogTray tray) throws Exception {
        DustResultType rt = DustResultType.REJECT;

        if (null != tray.entity) {
            RuntimeDataEntity e = entities.get(tray.entity);
            if (null != e) {
                rt = e.visit(visitor, tray);
            }
        } else {
            if (!entities.isEmpty()) {
                rt = visitor.agentAction(DustAgentAction.BEGIN, tray);
                if (rt != DustResultType.REJECT) {
                    for (Map.Entry<Integer, RuntimeDataEntity> e : entities.entrySet()) {
                        tray.entity = e.getKey();
                        e.getValue().visit(visitor, tray);
                    }
                }
                visitor.agentAction(DustAgentAction.END, tray);
            }
        }

        return rt;
    }

    public Integer find(RuntimeDataEntity e) {
        for ( Map.Entry<Integer, RuntimeDataEntity> ee : entities.entrySet() ) {
            if ( DustUtils.isEqual(e, ee.getValue()) ) {
                return ee.getKey();
            }
        }
        
        put(++lastId, e);
        
        return lastId;
    }
}
