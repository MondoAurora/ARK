package dust.gen;

import java.util.HashMap;

import dust.gen.DustGenConsts.DustException;

public class DustGenFactory<K, V> extends HashMap<K, V> {
    private static final long serialVersionUID = 1L;

    private final Class<V> cc;

    public DustGenFactory(Class<V> cc) {
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