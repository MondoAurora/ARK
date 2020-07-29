package dust.mod;

public interface ModuleTokens extends DustComponents {      
    class DustTokenModule extends DustToken {
        private static int start = 0;
        public DustTokenModule(int store, int id) {
            super(0, ++start);
        }
        
        public void setEntity(int entity) {
            this.entity = entity;
        }
    }
    
    DustTokenModule MiND_IdeaTypeType = new DustTokenModule(0, 0);
    DustTokenModule MiND_IdeaTypeMember = new DustTokenModule(0, 0);
    DustTokenModule MiND_IdeaTypeTag = new DustTokenModule(0, 0);
    DustTokenModule MiND_IdeaTypeConstant = new DustTokenModule(0, 0);
    
    DustTokenModule MiND_IdeaTagVal = new DustTokenModule(0, 0);
    DustTokenModule MiND_IdeaTagValInteger = new DustTokenModule(0, 0);
    DustTokenModule MiND_IdeaTagValReal = new DustTokenModule(0, 0);
    DustTokenModule MiND_IdeaTagValRef = new DustTokenModule(0, 0);
    
    DustTokenModule MiND_IdeaTagColl = new DustTokenModule(0, 0);
    DustTokenModule MiND_IdeaTagCollOne = new DustTokenModule(0, 0);
    DustTokenModule MiND_IdeaTagCollSet = new DustTokenModule(0, 0);
    DustTokenModule MiND_IdeaTagCollArr = new DustTokenModule(0, 0);
    DustTokenModule MiND_IdeaTagCollMap = new DustTokenModule(0, 0);
    
    
    DustTokenModule MiND_ModelTypeEntity = new DustTokenModule(0, 0);
    DustTokenModule MiND_ModelTypeStore = new DustTokenModule(0, 0);

    DustTokenModule MiND_ModelRefEntityStore = new DustTokenModule(0, 0);
    DustTokenModule MiND_ModelIntEntityStoreId = new DustTokenModule(0, 0);
    DustTokenModule MiND_ModelRefEntityGlobalId = new DustTokenModule(0, 0);

    DustTokenModule MiND_ModelRefEntityPrimaryType = new DustTokenModule(0, 0);
    DustTokenModule MiND_ModelRefEntityTypes = new DustTokenModule(0, 0);
    DustTokenModule MiND_ModelRefEntityOwner = new DustTokenModule(0, 0);
    DustTokenModule MiND_ModelRefEntityTags = new DustTokenModule(0, 0);
    
//    DustToken t1 = new DustTokenModule(0, 1);

}
