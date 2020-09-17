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
}