package dust.gen;

import java.util.HashMap;

public class DustGenFactory<K, V> extends HashMap<K, V> {
    private static final long serialVersionUID = 1L;

    private final Class<V> cc;

    public DustGenFactory(Class<V> cc) {
        this.cc = cc;
    }

    protected V createItem(K key, Object hint) {
        try {
            return cc.newInstance();
        } catch (Exception e) {
            return DustGenException.throwException(e, key);
        }
    }

    @SuppressWarnings("unchecked")
    public V get(Object key, Object hint) {
        V val = super.get(key);

        if (null == val) {
            val = createItem((K) key, hint);
            put((K) key, val);
        }

        return val;
    }

    @Override
    public V get(Object key) {
        return get(key, null);
    }
    
    public V peek(Object key) {
        return super.get(key);
    }
}