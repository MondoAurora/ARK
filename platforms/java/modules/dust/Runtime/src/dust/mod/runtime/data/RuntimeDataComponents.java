package dust.mod.runtime.data;

import dust.mod.DustComponents;
import dust.mod.runtime.RuntimeComponents;

public interface RuntimeDataComponents extends RuntimeComponents {
    interface RuntimeData extends RuntimeDataComponents, DustComponents.DustDialogAPI {
        
    }
    
    enum ValType {
        INTEGER, REAL, REF
    }
    
    enum CollType {
        SINGLE, SET, ARR, MAP
    }
}
