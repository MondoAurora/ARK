package dust.mod.runtime;

import dust.mod.DustComponents;

public interface RuntimeTokens extends DustComponents {      
    class DustTokenModule extends DustToken {
        public DustTokenModule(int store, int id, Object localOb) {
            super(store, id, localOb);
        }
        
    }
    
    DustToken t1 = new DustTokenModule(0, 1, null);
}