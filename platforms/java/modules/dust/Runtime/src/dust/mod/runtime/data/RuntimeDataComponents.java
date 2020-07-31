package dust.mod.runtime.data;

import dust.mod.DustComponents;
import dust.mod.runtime.RuntimeComponents;

public interface RuntimeDataComponents extends RuntimeComponents {
    interface RuntimeData extends RuntimeDataComponents, DustComponents.DustDialogAPI {
        
    }
    
    enum ValType {
        INTEGER(MiND_IdeaTagValInteger), REAL(MiND_IdeaTagValReal), REF(MiND_IdeaTagValRef);
        
        public final DustToken token;

        private ValType(DustToken token) {
            this.token = token;
        }
        
        public static ValType fromEntity(Integer entity) {
            for ( ValType v : values() ) {
                if ( v.token.getEntity() == entity ) {
                    return v;
                }
            }
            return null;
        }
    }
    
    enum CollType {
        ONE(MiND_IdeaTagCollOne), SET(MiND_IdeaTagCollSet), ARR(MiND_IdeaTagCollArr), MAP(MiND_IdeaTagCollMap);
        
        public final DustToken token;

        private CollType(DustToken token) {
            this.token = token;
        }
        
        public static CollType fromEntity(Integer entity) {
            for ( CollType v : values() ) {
                if ( v.token.getEntity() == entity ) {
                    return v;
                }
            }
            
            return null;
        }
    }
}
