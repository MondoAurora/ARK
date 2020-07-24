package dust.app;

import dust.mod.DustComponents;

public interface DustAppComponents extends DustComponents {
    interface NativeModule {
        Object createNative(Long type);
        void assignClass(Long type, String cName);
    }
    interface NativeApp {
        <RetType> RetType createNative(Long type);
        NativeModule addModule(String modName, String ... libNames);
    }
    interface NativeRuntime {
        void setApp(NativeApp app);
    }
}
