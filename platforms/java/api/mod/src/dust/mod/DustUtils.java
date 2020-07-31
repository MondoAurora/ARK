package dust.mod;

import java.io.PrintStream;
import java.util.HashMap;
import java.util.Map;

public class DustUtils implements DustComponents {
    private static PrintStream out = System.out;

    public static boolean isEqual(Object o1, Object o2) {
        return (null == o1) ? (null == o2) : (null != o2) && o1.equals(o2);
    }

    public static String toString(Object ob) {
        return (null == ob) ? "" : ob.toString();
    }

    public static StringBuilder sbAppend(StringBuilder sb, Object sep, boolean strict, Object... objects) {
        for (Object ob : objects) {
            String str = toString(ob);

            if (strict || (0 < str.length())) {
                if (null == sb) {
                    sb = new StringBuilder(str);
                } else {
                    if (0 < sb.length()) {
                        sb.append(sep);
                    }
                    sb.append(str);
                }
            }
        }
        return sb;
    }

    public static void log(DustEventLevel level, Object... stuff) {
        StringBuilder sb = sbAppend(null, " ", false, stuff);

        if (null != sb) {
            out.println(level + " " + sb.toString());
        }
    }

    public static class TokenUtils {
        public final int typeText;
        public final int refNative;
        public final int refTag;

        public TokenUtils(DustToken typeText, DustToken refNative, DustToken refTag) {
            this.typeText = typeText.getEntity();
            this.refNative = refNative.getEntity();
            this.refTag = refTag.getEntity();
        }

        public void setTextMember(int entity, int refToken, int key, String str) {
            DustDialogTray tray = new DustDialogTray();

            tray.entity = null;
            tray.token = typeText;
            Integer eParam = Dust.access(DustDialogCmd.ADD, tray);

            tray.entity = eParam;
            tray.token = refNative;
            tray.key = typeText;
            tray.value = str;
            Dust.access(DustDialogCmd.SET, tray);

            tray.entity = entity;
            tray.token = refToken;
            tray.key = key;
            tray.value = eParam;
            Dust.access(DustDialogCmd.SET, tray);
        }

        public String getTextMember(int entity, int refToken, int key, String defValue) {
            String ret = defValue;

            DustDialogTray tray = new DustDialogTray();
            tray.entity = entity;
            tray.token = refToken;
            tray.key = key;
            Integer eParam = Dust.access(DustDialogCmd.GET, tray);

            if (null != eParam) {
                tray.entity = eParam;
                tray.token = refNative;
                tray.key = typeText;
                ret = Dust.access(DustDialogCmd.GET, tray);
            }

            return ret;
        }

        public Map<DustToken, String> getTextParams(Map<DustToken, String> map, int entity, DustToken... members) {
            if ( null == map ) {
                map = new HashMap<>();
            } else {
                map.clear();
            }
            
            for ( DustToken t : members ) {
                String s = getTextMember(entity, t.getEntity(), 0, null);
                if ( null != s ) {
                    map.put(t, s);
                }
            }
            
            return map;
        }

        public void setMemberMeta(DustToken member, DustToken valType, DustToken collType) {
            DustDialogTray t = new DustDialogTray();
            t.entity = member.getEntity();
            t.token = refTag;

            t.value = valType.getEntity();
            Dust.access(DustDialogCmd.ADD, t);
            t.value = collType.getEntity();
            Dust.access(DustDialogCmd.ADD, t);
        }

    }

    public static class Factory<K, V> extends HashMap<K, V> {
        private static final long serialVersionUID = 1L;

        private final Class<V> cc;

        public Factory(Class<V> cc) {
            this.cc = cc;
        }

        protected V createItem(K key) {
            try {
                return cc.newInstance();
            } catch (Exception e) {
                return DustException.throwException(e, key);
            }
        }

        @SuppressWarnings("unchecked")
        @Override
        public V get(Object key) {
            V val = super.get(key);

            if (null == val) {
                val = createItem((K) key);
                put((K) key, val);
            }

            return val;
        }
    }

    public static boolean isEmpty(String str) {
        return (null == str) || str.isEmpty();
    }
}
