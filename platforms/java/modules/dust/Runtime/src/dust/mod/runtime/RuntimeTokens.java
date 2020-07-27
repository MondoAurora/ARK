package dust.mod.runtime;

public interface RuntimeTokens {  
    int CONST_NULL = 0;
    int CONST_FALSE = 1;
    int CONST_TRUE = 2;

    
    int VAL_INTEGER = 10;
    int VAL_REAL = 11;
    int VAL_REF = 12;
    
    
    int COLL_SINGLE = 20;
    
    int COLL_SET = 21;
    int COLL_ARR = 22;
    int COLL_MAP = 23;
    
    int VAR_ENTITY_PRIMARY_TYPE = 30;
    int VAR_ENTITY_STORE_ID = 31;
    
}
