#ifndef SRC_MODGEN_HTTPYHIROSE_H_
#define SRC_MODGEN_HTTPYHIROSE_H_


class HttpYHiroseModule : public DustModule {
public:
	virtual ~HttpYHiroseModule();

	virtual DustResultType DustResourceInit() ;
	virtual DustResultType DustResourceRelease();
};

#endif // SRC_MODGEN_HTTPYHIROSE_H_
