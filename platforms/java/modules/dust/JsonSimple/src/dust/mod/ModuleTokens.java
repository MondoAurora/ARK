package dust.mod;

public interface ModuleTokens extends DustComponents {  

    class DustTokenModule extends DustToken {
        public DustTokenModule(int store, int id) {
            super(store, id);
        }   
    }

    DustTokenModule MiND_ModelIntEntityStoreId = new DustTokenModule(0, 41);
    DustTokenModule MiND_ModelNativeEntityContent = new DustTokenModule(0, 43);
    
    DustTokenModule MiND_ModelRefEntityTags = new DustTokenModule(0, 47);

    DustTokenModule MiND_NativeRefModuleObjects = new DustTokenModule(0, 52);
    
    DustTokenModule TextTypeStatementImmutable = new DustTokenModule(0, 103);

    DustTokenModule JsonTypeConnector = new DustTokenModule(0, 400);

    DustUtils.TokenUtils TOKEN_UTILS = new DustUtils.TokenUtils(TextTypeStatementImmutable, MiND_ModelNativeEntityContent, MiND_ModelRefEntityTags);
}
