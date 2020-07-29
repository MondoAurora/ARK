package dust.mod;

import java.util.HashMap;

public class DustUtils implements DustComponents {
	public static boolean isEqual(Object o1, Object o2) {
		return ( null == o1 ) ? ( null == o2 ) : ( null != o2 ) && o1.equals(o2);
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
            
            if ( null == val ) {
                val = createItem((K) key);
                put((K) key, val);
            }
            
            return val;
        }
	}
}
