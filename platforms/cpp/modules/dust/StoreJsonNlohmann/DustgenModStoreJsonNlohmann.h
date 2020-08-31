#ifndef SRC_MODGEN_STOREQJSON_H_
#define SRC_MODGEN_STOREQJSON_H_


class StoreJsonNlohmannModule : public DustModule {
public:
	virtual ~StoreJsonNlohmannModule();

	virtual DustResultType DustResourceInit() ;
	virtual DustResultType DustResourceRelease();
};

#endif // SRC_MODGEN_STOREQJSON_H_
