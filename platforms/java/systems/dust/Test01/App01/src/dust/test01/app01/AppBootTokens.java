package dust.test01.app01;

import dust.app.DustAppComponents;
import dust.mod.DustUtils;

public interface AppBootTokens extends DustAppComponents {  

    
    DustToken MiND_IdeaTypeTag = new DustToken(0, 2);
    DustToken MiND_IdeaTypeConstant = new DustToken(0, 3);
    
    DustToken MiND_IdeaTagVal = new DustToken(0, 10);
    DustToken MiND_IdeaTagValInteger = new DustToken(0, 11);
    DustToken MiND_IdeaTagValReal = new DustToken(0, 12);
    DustToken MiND_IdeaTagValRef = new DustToken(0, 13);
    
    DustToken MiND_IdeaTagColl = new DustToken(0, 20);
    DustToken MiND_IdeaTagCollOne = new DustToken(0, 21);
    DustToken MiND_IdeaTagCollSet = new DustToken(0, 22);
    DustToken MiND_IdeaTagCollArr = new DustToken(0, 23);
    DustToken MiND_IdeaTagCollMap = new DustToken(0, 24);

    DustToken MiND_ModelRefEntityTags = new DustToken(0, 47);

    DustToken MiND_ModelNativeEntityContent = new DustToken(0, 43);
    
    DustToken MiND_NativeTypeModule = new DustToken(0, 50);
    DustToken MiND_NativeRefModuleObjects = new DustToken(0, 52);

    
    DustToken TextTypeStatementImmutable = new DustToken(0, 103);

    DustToken GuardTypeAccount = new DustToken(0, 300);
    DustToken GuardRefAccountId = new DustToken(0, 301);
    DustToken GuardRefAccountPass = new DustToken(0, 302);

    DustToken JdbcTypeConnector = new DustToken(0, 200);
    DustToken JdbcRefConnectorDriver = new DustToken(0, 201);
    DustToken JdbcRefConnectorPath = new DustToken(0, 202);
 
    DustToken JsonTypeConnector = new DustToken(0, 400);

    AppTokens APP_TOKENS = new AppTokens(MiND_NativeTypeModule, TextTypeStatementImmutable, MiND_NativeRefModuleObjects, MiND_ModelNativeEntityContent);
}
