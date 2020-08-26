#ifndef SRC_MODGEN_STOREQJSON_H_
#define SRC_MODGEN_STOREQJSON_H_


class StoreQJsonModule : public DustModule {
public:
	virtual ~StoreQJsonModule();

	virtual DustResultType DustResourceInit() ;
	virtual DustResultType DustResourceRelease();
};

#endif // SRC_MODGEN_STOREQJSON_H_
