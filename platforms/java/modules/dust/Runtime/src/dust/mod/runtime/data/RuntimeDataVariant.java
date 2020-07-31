package dust.mod.runtime.data;

import dust.mod.DustUtils;
import dust.mod.runtime.data.RuntimeDataComponents.RuntimeData;

public class RuntimeDataVariant implements RuntimeData {
    RuntimeDataTokenInfo token;

    Integer key;
    Object value;
    RuntimeDataCollection coll;

    public RuntimeDataVariant(RuntimeDataTokenInfo token, Object value, Integer key) {
        this.token = token;
        this.value = value;
        this.key = key;
    }

    boolean isValid() {
        return (null != value) || ((coll != null) && coll.isValid());
    }

    @SuppressWarnings("unchecked")
    @Override
    public <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray) {
        Object ret = null;

        if (CollType.ONE == token.getCollType()) {
            switch (cmd) {
            case CHK:
                ret = DustUtils.isEqual(value, tray.value);
            case DEL:
                value = null;
                ret = true;
                break;
            case GET:
                ret = value;
                break;
            case SET:
            case ADD:
                ret = value;
                value = tray.value;
                break;
            }
        } else {
            ret = (null == coll) ? RuntimeDataCollection.access(cmd, tray, this) : coll.access(cmd, tray);
        }

        return (RetType) ret;
    }

    @Override
    public DustResultType visit(DustAgent visitor, DustDialogTray tray) throws Exception {
        DustResultType rt = DustResultType.REJECT;

        if (null == coll) {
            if (null != value) {
                tray.key = key;
                tray.value = value;
                rt = visitor.agentAction(DustAgentAction.PROCESS, tray);
            }
        } else {
            coll.visit(visitor, tray);
        }

        return rt;
    }
}
