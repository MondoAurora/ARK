package dust.mod.runtime.data;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import dust.mod.DustUtils;
import dust.mod.runtime.data.RuntimeDataComponents.RuntimeData;

public abstract class RuntimeDataCollection implements RuntimeData {

    private static class CollSet extends RuntimeDataCollection {
        Set<Object> set = new HashSet<>();

        CollSet(RuntimeDataVariant var, DustDialogTray tray) {
            set.add(var.value);
            set.add(tray.value);

            var.value = null;
            var.key = null;
        }

        @Override
        public DustResultType visit(DustAgent visitor, DustDialogTray tray) throws Exception {
            DustResultType rt = DustResultType.REJECT;

            if (set.isEmpty()) {
                return rt;
            }

            rt = visitor.agentAction(DustAgentAction.BEGIN, tray);
            tray.key = 0;

            if (DustResultType.REJECT != rt) {
                for (Object o : set) {
                    tray.value = o;
                    rt = visitor.agentAction(DustAgentAction.PROCESS, tray);
                }
            }

            visitor.agentAction(DustAgentAction.END, tray);

            return rt;
        }

        @SuppressWarnings("unchecked")
        public static <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray, RuntimeDataVariant var) {
            Object ret = null;
            boolean valMatch = (null == tray.value) || DustUtils.isEqual(var.value, tray.value);

            switch (cmd) {
            case CHK:
                ret = valMatch;
                break;
            case DEL:
                if (valMatch) {
                    ret = true;
                    var.value = null;
                } else {
                    ret = false;
                }
                break;
            case GET:
                ret = var.value;
                break;
            case SET:
                if (valMatch) {
                    ret = false;
                } else {
                    var.value = tray.value;
                    ret = true;
                }
                break;
            case ADD:
                if (valMatch) {
                    ret = false;
                } else {
                    var.coll = new CollSet(var, tray);
                }
                break;
            }

            return (RetType) ret;
        }

        @SuppressWarnings("unchecked")
        @Override
        public <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray) {
            Object ret = null;

            switch (cmd) {
            case CHK:
            case GET:
                ret = (null == tray.value) || set.contains(tray.value);
                break;
            case DEL:
                if (null == tray.value) {
                    set.clear();
                    ret = true;
                } else {
                    ret = set.remove(tray.value);
                }
                break;
            case SET:
                if ((1 == set.size()) && set.contains(tray.value)) {
                    ret = false;
                } else {
                    set.clear();
                    if (null != tray.value) {
                        set.add(tray.value);
                    }
                    ret = true;
                }
                break;
            case ADD:
                if (set.contains(tray.value)) {
                    ret = false;
                } else {
                    set.add(tray.value);
                    ret = true;
                }
                break;
            }

            return (RetType) ret;
        }

        @Override
        public boolean isValid() {
            return !set.isEmpty();
        }
    }

    private static class CollArr extends RuntimeDataCollection {
        ArrayList<Object> arr = new ArrayList<>();

        CollArr(RuntimeDataVariant var, DustDialogTray tray) {
            arr.add(var.value);
            arr.add(tray.value);

            var.value = null;
            var.key = null;
        }

        @Override
        public DustResultType visit(DustAgent visitor, DustDialogTray tray) throws Exception {
            DustResultType rt = DustResultType.REJECT;

            if (arr.isEmpty()) {
                return rt;
            }

            rt = visitor.agentAction(DustAgentAction.BEGIN, tray);
            tray.key = 0;

            if (DustResultType.REJECT == rt) {
                for (Object o : arr) {
                    tray.value = o;
                    ++tray.key;
                    rt = visitor.agentAction(DustAgentAction.PROCESS, tray);
                }
            }

            visitor.agentAction(DustAgentAction.END, tray);

            return rt;
        }

        @SuppressWarnings("unchecked")
        public static <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray, RuntimeDataVariant var) {
            Object ret = null;
            boolean valMatch = (null == tray.value) || DustUtils.isEqual(var.value, tray.value);
            boolean keyMatch = (null == tray.key) || DustUtils.isEqual(0, tray.key);

            switch (cmd) {
            case CHK:
                ret = valMatch && keyMatch;
                break;
            case DEL:
                if (valMatch && keyMatch) {
                    ret = true;
                    var.value = null;
                } else {
                    ret = false;
                }
                break;
            case GET:
                ret = keyMatch ? var.value : tray.value;
                break;
            case SET:
                if (keyMatch) {
                    if (valMatch) {
                        ret = false;
                    } else {
                        var.value = tray.value;
                        ret = true;
                    }
                } else if (1 == tray.key) {
                    var.coll = new CollArr(var, tray);
                }
                break;
            case ADD:
                var.coll = new CollArr(var, tray);
                break;
            }

            return (RetType) ret;
        }

        @SuppressWarnings("unchecked")
        @Override
        public <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray) {
            Object ret = null;
            boolean idxOk = ((null != tray.key) && (0 <= tray.key) && (tray.key < arr.size()));
            Object at = idxOk ? arr.get(tray.key) : null;

            switch (cmd) {
            case CHK:
                ret = (null == tray.value) ? idxOk : DustUtils.isEqual(at, tray.value);
                break;
            case GET:
                ret = idxOk ? at : tray.value;
                break;
            case DEL:
                if (idxOk) {
                    arr.remove(tray.key);
                    ret = true;
                } else if ( null != tray.value ){
                    ret = arr.remove(tray.value);
                } else {
                    arr.clear();
                    ret = true;
                }
                break;
            case SET:
                if (idxOk) {
                    ret = at;
                    arr.set(tray.key, tray.value);
                } else if (DustUtils.isEqual(arr.size(), tray.key)) {
                        arr.add(tray.value);
                } else if ( null == tray.key ) {
                    arr.clear();
                    arr.add(tray.value);                    
                }
                break;
            case ADD:
                arr.add(tray.value);                    
                break;
            }

            return (RetType) ret;
        }

        @Override
        public boolean isValid() {
            return !arr.isEmpty();
        }
    }

    private static class CollMap extends RuntimeDataCollection {
        Map<Integer, Object> map = new HashMap<>();

        CollMap(RuntimeDataVariant var, DustDialogTray tray) {
            map.put(var.key, var.value);
            map.put(tray.key, tray.value);
            var.value = null;
            var.key = null;
        }

        @Override
        public DustResultType visit(DustAgent visitor, DustDialogTray tray) throws Exception {
            DustResultType rt = DustResultType.REJECT;

            if (map.isEmpty()) {
                return rt;
            }

            rt = visitor.agentAction(DustAgentAction.BEGIN, tray);

            if (DustResultType.REJECT == rt) {
                for (Map.Entry<Integer, Object> v : map.entrySet()) {
                    tray.key = v.getKey();
                    tray.value = v.getValue();
                    visitor.agentAction(DustAgentAction.PROCESS, tray);
                }
            }

            visitor.agentAction(DustAgentAction.END, tray);

            return rt;
        }
        
        @SuppressWarnings("unchecked")
        public static <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray, RuntimeDataVariant var) {
            Object ret = null;
            boolean valMatch = (null == tray.value) || DustUtils.isEqual(var.value, tray.value);
            boolean keyMatch = (null == tray.key) || DustUtils.isEqual(var.key, tray.key);

            switch (cmd) {
            case CHK:
                ret = valMatch && keyMatch;
                break;
            case DEL:
                if (valMatch && keyMatch) {
                    ret = true;
                    var.value = null;
                } else {
                    ret = false;
                }
                break;
            case GET:
                ret = keyMatch ? var.value : tray.value;
                break;
            case SET:
            case ADD:
                if (keyMatch) {
                    if (valMatch) {
                        ret = false;
                    } else {
                        var.value = tray.value;
                        ret = true;
                    }
                } else if (null != tray.key) {
                    var.coll = new CollMap(var, tray);
                }
                break;
            }

            return (RetType) ret;
        }

        @SuppressWarnings("unchecked")
        @Override
        public <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray) {
            Object ret = null;
            Object at = (null != tray.key) ? map.get(tray.key) : null;

            switch (cmd) {
            case CHK:
                ret = (null == tray.value) ? (null != at) : DustUtils.isEqual(at, tray.value);
                break;
            case GET:
                ret = (null != at) ? at : tray.value;
                break;
            case DEL:
                if (null != tray.key) {
                    if (null != at) {
                        map.remove(tray.key);
                        ret = at;
                    }
                } else {
                    map.clear();
                    ret = true;
                }
                break;
            case SET:
            case ADD:
                if ((null != tray.key) && !DustUtils.isEqual(at, tray.value)) {
                    ret = at;
                    map.put(tray.key, tray.value);
                }
                break;
            }

            return (RetType) ret;
        }

        @Override
        public boolean isValid() {
            return !map.isEmpty();
        }
    }

    public abstract boolean isValid();

    public static <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray, RuntimeDataVariant var) {
        switch (var.token.getCollType()) {
        case SET:
            return CollSet.access(cmd, tray, var);
        case ARR:
            return CollArr.access(cmd, tray, var);
        case MAP:
            return CollMap.access(cmd, tray, var);
        default:
            return null;
        }
    }
}
