package dust.gen;

import java.util.HashMap;

public class DustGenTranslator<Left, Right> {
    HashMap<Left, Right> l2r = new HashMap<>();
    HashMap<Right, Left> r2l = new HashMap<>();
    
    public DustGenTranslator() {
    }

    public DustGenTranslator(Left[] lefts, Right[] rights) {
        int l = lefts.length;
        
        if ( l != rights.length ) {
            throw new RuntimeException("Different lengths!");
        }
        for ( int i = 0; i < l; ++i ) {
            add(lefts[i], rights[i]);
        }
    }

    public void add(Left l, Right r) {
        l2r.put(l, r);
        r2l.put(r, l);
    }
    
    public Left getLeft(Right r) {
        return r2l.get(r);
    }
    
    public Right getRight(Left l) {
        return l2r.get(l);
    } 
    
    public boolean contains(Object o) {
        return r2l.containsKey(o) || l2r.containsKey(o);
    }
    
    public boolean containsRight(Right r) {
        return r2l.containsKey(r);
    }
    
    public boolean containsLeft(Left l) {
        return l2r.containsKey(l);
    }

	public void clear() {
		l2r.clear();
		r2l.clear();
	}

	public Iterable<Left> getLeftAll() {
		return l2r.keySet();
	}

	public Iterable<Right> getRightAll() {
		return r2l.keySet();
	}

	public boolean isEmpty() {
		return l2r.isEmpty();
	}
}