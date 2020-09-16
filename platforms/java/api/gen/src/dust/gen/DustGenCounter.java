package dust.gen;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.TreeMap;

public class DustGenCounter implements Iterable<Map.Entry<Object, Long>>{
    Map<Object, Long> counts;
    
    public DustGenCounter() {
        this(false);
    }
    public DustGenCounter(boolean sorted) {
        counts = sorted ? new TreeMap<>() : new HashMap<>();
    }
    
    public void reset() {
        counts.clear();
    }
    
    public void add(Object ob) {
        Long l = counts.get(ob);
        counts.put(ob, (null == l) ? 1 : l+1);
    }
    
    @Override
    public String toString() {
        StringBuilder sb = null;
        for ( Map.Entry<Object, Long> e : this ) {
            sb = DustGenUtils.sbAppend(sb, ", ", false, e.getKey());
            DustGenUtils.sbAppend(sb, "", false, ": ", e.getValue());
        }
        return DustGenUtils.toStringSafe(sb);
    }
    
    @Override
    public Iterator<Entry<Object, Long>> iterator() {
        return counts.entrySet().iterator();
    }
}
