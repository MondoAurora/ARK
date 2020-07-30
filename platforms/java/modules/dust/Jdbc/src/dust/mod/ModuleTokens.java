package dust.mod;

public interface ModuleTokens extends DustComponents {  

    class DustTokenModule extends DustToken {
        public DustTokenModule(int store, int id) {
            super(store, id);
        }
        
    }
    

    DustTokenModule MiND_ModelNativeEntityContent = new DustTokenModule(0, 43);
    DustTokenModule TextTypeStatementImmutable = new DustTokenModule(0, 103);

    DustTokenModule GuardTypeAccount = new DustTokenModule(0, 300);
    DustTokenModule GuardRefAccountId = new DustTokenModule(0, 301);
    DustTokenModule GuardRefAccountPass = new DustTokenModule(0, 302);

    DustTokenModule JdbcTypeConnector = new DustTokenModule(0, 200);
    DustTokenModule JdbcRefConnectorPath = new DustTokenModule(0, 201);

    
//    DustToken t1 = new DustTokenModule(0, 1);
    
}
