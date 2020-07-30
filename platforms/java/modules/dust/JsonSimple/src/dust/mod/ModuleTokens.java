package dust.mod;

public interface ModuleTokens extends DustComponents {  

    class DustTokenModule extends DustToken {
        public DustTokenModule(int store, int id) {
            super(store, id);
        }
        
    }
    
    DustTokenModule MiND_ModelIntEntityStoreId = new DustTokenModule(0, 41);
    DustTokenModule MiND_ModelNativeEntityContent = new DustTokenModule(0, 43);
    DustTokenModule TextTypeStatementImmutable = new DustTokenModule(0, 103);

    
//    DustToken t1 = new DustTokenModule(0, 1);
    
}
