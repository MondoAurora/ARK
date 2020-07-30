package dust.mod;

import java.io.PrintStream;
import java.util.HashMap;

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
        
        if ( null != sb ) {
            out.println(level + " " + sb.toString());
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
}
