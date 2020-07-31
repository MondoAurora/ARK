package dust.mod;

public interface ModuleTokens extends DustComponents {  

    class DustTokenModule extends DustToken {
        public DustTokenModule(int store, int id) {
            super(store, id);
        }
        
    }
    
    
    DustTokenModule MiND_ModelNativeEntityContent = new DustTokenModule(0, 43);
    
    DustTokenModule MiND_ModelRefEntityTags = new DustTokenModule(0, 47);

    DustTokenModule MiND_NativeRefModuleObjects = new DustTokenModule(0, 52);
    
    DustTokenModule TextTypeStatementImmutable = new DustTokenModule(0, 103);
    DustTokenModule TextRefIdentifiedId = new DustTokenModule(0, 111);

    DustTokenModule MiND_IdeaTagValRef = new DustTokenModule(0, 13);
    DustTokenModule MiND_IdeaTagCollOne = new DustTokenModule(0, 21);

    
    DustTokenModule GuardTypeAccount = new DustTokenModule(0, 300);
    DustTokenModule GuardRefAccountId = new DustTokenModule(0, 301);
    DustTokenModule GuardRefAccountPass = new DustTokenModule(0, 302);

    DustTokenModule JdbcTypeConnector = new DustTokenModule(0, 200);
    DustTokenModule JdbcRefConnectorDriver = new DustTokenModule(0, 201);
    DustTokenModule JdbcRefConnectorPath = new DustTokenModule(0, 202);

    DustUtils.TokenUtils TOKEN_UTILS = new DustUtils.TokenUtils(TextTypeStatementImmutable, MiND_ModelNativeEntityContent, MiND_ModelRefEntityTags);
    
}
