package dust.gen;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Collection;
import java.util.Date;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

public class DustGenUtils implements DustGenConsts {

    public interface HasDefault<T> {
        T getDefault();
    }

    public interface ItemCreator<T> {
        T create();
    }
    
    @SuppressWarnings("rawtypes")
    public static Object resolvePath(Object src, Object... path ) {
        Object current = src;
        
        for ( Object member : path ) {
            current = ((Map)current).get(member);
            if ( null == current ) {
                break;
            }
        }
        
        return current;
    }
    
    public static String strTimestamp() {
        SimpleDateFormat sdf = new SimpleDateFormat("YYYY-MM-dd_HH-mm-ss_SSS");
        return sdf.format(new Date());
    }
    
    public static String strTimestamp(long time) {
        SimpleDateFormat sdf = new SimpleDateFormat("YYYY-MM-dd_HH-mm-ss_SSS");
        return sdf.format(new Date(time));
    }
    
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

    public static boolean isEmpty(String str) {
        return (null == str) || str.isEmpty();
    }
    
	public static File ensureParents(File f) {
		f.getParentFile().mkdirs();
		return f;
	}
    
    private static final Map<Class<?>, Map<String, Enum<?>>> ENUM_MAP = new HashMap<Class<?>, Map<String,Enum<?>>>();

    @SuppressWarnings("unchecked")
    public static <T extends Enum<T>> T fromString(String str, Class<T> ec) {
        Map<String, Enum<?>> m;
        
        synchronized (ENUM_MAP) {
            m = ENUM_MAP.get(ec);
            
            if ( null == m ) {
                m = new TreeMap<>();
                for ( Enum<?> e : ec.getEnumConstants() ) {
                    m.put(e.name(), e);
                }
                ENUM_MAP.put(ec, m);
            }
        }
        
        return (T) m.get(str);
    }

    public static boolean enumMatch(Object str, Enum<?> e) {
        return e.name().equals(str);
    }

    public static <T extends Enum<T>> T fromString(String str, T defVal) {
        @SuppressWarnings("unchecked")
        T ret = (T) fromString(str, defVal.getClass());
        return (null == ret) ? defVal : ret;
    }

    public static StringBuilder collToString(String sep, Collection<?> coll) {
        if ((null == coll) || coll.isEmpty()) {
            return null;
        }

        StringBuilder sb = null;

        for (Object o : coll) {
            String s = toStringSafe(o);
            if (!isEmpty(s)) {
                if (null == sb) {
                    sb = new StringBuilder();
                } else {
                    sb.append(sep);
                }
                sb.append(s);
            }
        }

        return sb;
    }

    public static String toStringSafe(Object value) {
        return (null == value) ? null : value.toString();
    }

    public static boolean contains(Object ob, Object... options) {
        for ( Object o : options) {
            if ( ob.equals(o)) {
                return true;
            }
        }
        return false;
    }
    
    private static final EnumSet<DustResultType> RT_READ = EnumSet.of(DustResultType.READ, DustResultType.ACCEPT_READ);
    private static final EnumSet<DustResultType> RT_REJECT = EnumSet.of(DustResultType.NOTIMPLEMENTED, DustResultType.REJECT);
    
    public static boolean isReadOn(DustResultType rt) {
    	return RT_READ.contains(rt);
    }
    public static boolean isReject(DustResultType rt) {
    	return RT_REJECT.contains(rt);
    }
}
