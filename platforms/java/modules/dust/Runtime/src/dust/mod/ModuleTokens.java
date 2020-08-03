package dust.mod;

public interface ModuleTokens extends DustComponents {      
    class DustTokenModule extends DustToken {
        public DustTokenModule(int store, int id) {
            super(store, id);
        }
        
        public void setEntity(int entity) {
            this.entity = entity;
        }
    }
    
    DustTokenModule MiND_IdeaTypeType = new DustTokenModule(0, 0);
    DustTokenModule MiND_IdeaTypeMember = new DustTokenModule(0, 1);
    DustTokenModule MiND_IdeaTypeTag = new DustTokenModule(0, 2);
    DustTokenModule MiND_IdeaTypeConstant = new DustTokenModule(0, 3);
    
    DustTokenModule MiND_IdeaTagVal = new DustTokenModule(0, 10);
    DustTokenModule MiND_IdeaTagValInteger = new DustTokenModule(0, 11);
    DustTokenModule MiND_IdeaTagValReal = new DustTokenModule(0, 12);
    DustTokenModule MiND_IdeaTagValRef = new DustTokenModule(0, 13);
    
    DustTokenModule MiND_IdeaTagColl = new DustTokenModule(0, 20);
    DustTokenModule MiND_IdeaTagCollOne = new DustTokenModule(0, 21);
    DustTokenModule MiND_IdeaTagCollSet = new DustTokenModule(0, 22);
    DustTokenModule MiND_IdeaTagCollArr = new DustTokenModule(0, 23);
    DustTokenModule MiND_IdeaTagCollMap = new DustTokenModule(0, 24);
    
    
    DustTokenModule MiND_ModelTypeEntity = new DustTokenModule(0, 30);
    DustTokenModule MiND_ModelTypeStore = new DustTokenModule(0, 31);

    DustTokenModule MiND_ModelRefEntityStore = new DustTokenModule(0, 40);
    DustTokenModule MiND_ModelIntEntityStoreId = new DustTokenModule(0, 41);
    DustTokenModule MiND_ModelRefEntityGlobalId = new DustTokenModule(0, 42);

    DustTokenModule MiND_ModelNativeEntityContent = new DustTokenModule(0, 43);

    DustTokenModule MiND_ModelRefEntityPrimaryType = new DustTokenModule(0, 44);
    DustTokenModule MiND_ModelRefEntityTypes = new DustTokenModule(0, 45);
    DustTokenModule MiND_ModelRefEntityOwner = new DustTokenModule(0, 46);
    DustTokenModule MiND_ModelRefEntityTags = new DustTokenModule(0, 47);
    
    DustTokenModule MiND_NativeTypeModule = new DustTokenModule(0, 50);
    DustTokenModule MiND_NativeRefModuleLibraries = new DustTokenModule(0, 51);
    DustTokenModule MiND_NativeRefModuleObjects = new DustTokenModule(0, 52);
    
    
    DustTokenModule TextTypeLanguage = new DustTokenModule(0, 100);
    DustTokenModule TextConstLanguageTokens = new DustTokenModule(0, 101);
    DustTokenModule TextTypeStatementMutable = new DustTokenModule(0, 102);
    DustTokenModule TextTypeStatementImmutable = new DustTokenModule(0, 103);
    
    DustTokenModule TextTypeIdentified = new DustTokenModule(0, 110);
    DustTokenModule TextRefIdentifiedId = new DustTokenModule(0, 111);
}
