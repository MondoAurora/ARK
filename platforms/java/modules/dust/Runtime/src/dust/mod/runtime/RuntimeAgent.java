package dust.mod.runtime;

import java.util.Map;

import dust.gen.DustGenException;
import dust.gen.DustGenFactory;
import dust.mod.Dust;
import dust.mod.Dust.DustDialogAPI;
import dust.mod.DustComponents;
import dust.mod.runtime.data.RuntimeDataComponents.CollType;
import dust.mod.runtime.data.RuntimeDataComponents.ValType;
import dust.mod.runtime.data.RuntimeDataEntity;
import dust.mod.runtime.data.RuntimeDataStore;
import dust.mod.runtime.data.RuntimeDataTokenInfo;

public class RuntimeAgent implements DustComponents, Dust.DustDialogAPI, DustComponents.DustAgent, DustComponents.DustTokenResolver, RuntimeComponents {
    private static RuntimeAgent THE_AGENT;

    NativeApp app = null;
    private final DustGenFactory<Integer, RuntimeDataTokenInfo> tokens = new DustGenFactory<Integer, RuntimeDataTokenInfo>(null) {
        private static final long serialVersionUID = 1L;

        @Override
        protected RuntimeDataTokenInfo createItem(Integer key, Object hint) {
            RuntimeDataTokenInfo rti = new RuntimeDataTokenInfo();
            rti.load(key);
            return rti;
        };
    };

    enum FirstEntities {
        NULL, STORE_0, TYPE_STORE, TYPE_TYPE, TYPE_MEMBER, TYPE_TAG,
    };

    int nextToken = FirstEntities.values().length;

    RuntimeDataStore mainStore = new RuntimeDataStore();
    private final DustGenFactory<Integer, RuntimeDataStore> stores = new DustGenFactory<>(RuntimeDataStore.class);

    public void boot() {
        addBootToken(MiND_ModelRefEntityStore, ValType.REF, CollType.ONE);
        addBootToken(MiND_ModelIntEntityStoreId, ValType.INTEGER, CollType.ONE);

        addBootToken(MiND_ModelRefEntityPrimaryType, ValType.REF, CollType.ONE);
        addBootToken(MiND_ModelRefEntityTypes, ValType.REF, CollType.SET);
        addBootToken(MiND_ModelRefEntityTags, ValType.REF, CollType.SET);
        addBootToken(MiND_ModelNativeEntityContent, ValType.REF, CollType.MAP);

        addBootToken(TextRefIdentifiedId, ValType.REF, CollType.ONE);
        addBootToken(MiND_NativeRefModuleLibraries, ValType.REF, CollType.SET);
        addBootToken(MiND_NativeRefModuleObjects, ValType.REF, CollType.MAP);

        mainStore.getEntity(FirstEntities.STORE_0.ordinal(), FirstEntities.TYPE_STORE.ordinal());

        for (Map.Entry<Integer, RuntimeDataTokenInfo> eRti : tokens.entrySet()) {
            createTokenEntity(eRti.getKey(), eRti.getValue());
        }
    }

    void addBootToken(DustTokenModule token, ValType valType, CollType collType) {
        int entity = nextToken++;
        tokens.put(entity, new RuntimeDataTokenInfo(token, valType, collType));
        token.setEntity(entity);
    }

    public void createTokenEntity(int id, RuntimeDataTokenInfo rti) {
        RuntimeDataEntity e = stores.get(rti.getStore()).getEntity(rti.getStoreId(), FirstEntities.TYPE_MEMBER.ordinal());
        DustDialogTray tray = new DustDialogTray();

        tray.setToken(MiND_ModelIntEntityStoreId);
        tray.value = FirstEntities.STORE_0.ordinal();
        e.access(DustDialogCmd.SET, tray);

        tray.setToken(MiND_ModelRefEntityTags);
        switch (rti.getValType()) {
        case INTEGER:
            tray.value = MiND_IdeaTagValInteger.getEntity();
            break;
        case REAL:
            tray.value = MiND_IdeaTagValReal.getEntity();
            break;
        case REF:
            tray.value = MiND_IdeaTagValRef.getEntity();
            break;
        }
        e.access(DustDialogCmd.ADD, tray);
        switch (rti.getCollType()) {
        case ONE:
            tray.value = MiND_IdeaTagCollOne.getEntity();
            break;
        case SET:
            tray.value = MiND_IdeaTagCollSet.getEntity();
            break;
        case ARR:
            tray.value = MiND_IdeaTagCollArr.getEntity();
            break;
        case MAP:
            tray.value = MiND_IdeaTagCollMap.getEntity();
            break;
        }
        e.access(DustDialogCmd.ADD, tray);

        mainStore.put(id, e);
    }

    @Override
    public <RetType> RetType access(DustDialogCmd cmd, DustDialogTray tray) {
        return mainStore.access(cmd, tray);
    }

    @Override
    public DustResultType visit(DustAgent visitor, DustDialogTray tray) throws Exception {
        return mainStore.visit(visitor, tray);
    }

    @Override
    public DustResultType agentAction(DustAgentAction action, DustDialogTray tray) throws Exception {
        return DustResultType.ACCEPT;
    }

    public RuntimeDataTokenInfo getToken_(int entity) {
        RuntimeDataTokenInfo rt = tokens.get(entity);

        if (null == rt) {

        }

        return rt;
    }

    void test() {
        mainStore.getEntity(-3, -3);

        DustDialogTray tray = new DustDialogTray();
        tray.entity = -3;
        tray.setToken(MiND_ModelIntEntityStoreId);
        tray.value = 42;

        THE_AGENT.access(DustDialogCmd.SET, tray);

        tray.setToken(MiND_ModelNativeEntityContent);
        tray.key = TextTypeStatementImmutable.getEntity();
        tray.value = "Hello world!";
        THE_AGENT.access(DustDialogCmd.SET, tray);

        try {
            agentAction(DustAgentAction.PROCESS, null);
        } catch (Exception e) {
            DustGenException.throwException(e);
        }
    }

    @Override
    public int getTokenMember(DustToken token) {
        int storeId = app.getSystemStoreIdx(token);
        RuntimeDataEntity e = stores.get(storeId).getEntity(token.id, FirstEntities.TYPE_MEMBER.ordinal());

        return mainStore.find(e);
    }

    public static RuntimeDataTokenInfo getToken(int entity) {
        return THE_AGENT.getToken_(entity);
    }

    public static Object createNative(int type) {
        return THE_AGENT.app.createNative(type);
    }

    public static DustDialogAPI createRuntime(NativeApp app) {
        THE_AGENT = new RuntimeAgent();

        THE_AGENT.app = app;

        Dust.init(THE_AGENT);

        THE_AGENT.boot();

        THE_AGENT.test();

        return THE_AGENT;
    }

    public static void launch() {
    }
}
