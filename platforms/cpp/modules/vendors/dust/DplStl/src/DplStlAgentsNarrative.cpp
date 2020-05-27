#include "DplStl.h"

using namespace DustUnitMindGeneric;

DplStlLogicControl::DplStlLogicControl() :firstCall(true), pos(0), inSep(false) {}

void DplStlLogicControl::requestRelay(DustEntity relay) {
	DplStlLogicPDA *pAgent = DplStlRuntime::getCurrentCore()->getDialog()->getCurrentPda();
	DplStlLogicState *pBlockCurrent = pAgent->getCurrentState();

	DplStlLogicState *pBlockRelay = mapChildBlocks[relay];
	if (!pBlockRelay) {
		pBlockRelay = new DplStlLogicState();
		DplStlDataEntity *pe = pBlockCurrent->getEntity(relay);
		pBlockRelay->init(pe, pBlockCurrent);
		mapChildBlocks[relay] = pBlockRelay;
	}

	pAgent->relayEntry(pBlockRelay);
}

DustResultType DplStlLogicControl::optGetChildResult(DustResultType defRet ) {
	if (firstCall) {
		firstCall = false;
		return defRet;
	} else {
		return DplStlRuntime::getCurrentCore()->lastResult;
	}
}

DplStlLogicControl::~DplStlLogicControl() {
	for (StateIterator iter = mapChildBlocks.begin(); iter != mapChildBlocks.end(); ++iter) {
		DplStlLogicState *pb = iter->second;
		delete pb;
	}
}

DustResultType DplStlLogicControl::optRelayChild() {
	DustResultType ret = optGetChildResult();

	bool rp = DUST_RESULT_ACCEPT_PASS == ret;

	if (rp || (DUST_RESULT_ACCEPT == ret)) {
		DustRef ctx(DUST_CTX_SELF);

		bool coll = isColl();
		unsigned int limit = coll ? DustData::getMemberCount(ctx, DustRefCollectionMembers) : (unsigned) DustData::getInteger(ctx, DustIntLimitsMax, INT_MAX);

		if (pos < limit) {
			DustEntity r = coll ? DustData::getRef(ctx, DustRefCollectionMembers, pos) : DustData::getRef(ctx, DustRefLinkTarget, 0);
			DustEntity eSep = DustData::getRef(ctx, DustRefCollectionSeparator, 0);

			if (eSep) {
				if (inSep) {
					inSep = false;
					r = eSep;
				} else {
					inSep = true;
					++pos;
				}
			} else {
				++pos;
			}

			requestRelay(r);
			ret = DUST_RESULT_READ;
		} else {
			ret = rp ? DUST_RESULT_ACCEPT_PASS : DUST_RESULT_ACCEPT;
		}
	}

	return ret;
}

DustResultType DplStlLogicSequence::DustActionExecute() {
	return optRelayChild();
}

DustResultType DplStlLogicRepeat::DustActionExecute() {
	DustResultType ret = optRelayChild();

	if ( DUST_RESULT_REJECT == ret ) {
		DustRef ctx(DUST_CTX_SELF);
		int min = DustData::getInteger(ctx, DustUnitMindGeneric::DustIntLimitsMin, 1);

		if ( min <= (int) pos ) {
			ret = DUST_RESULT_ACCEPT_PASS;
		}
	}

	return ret;
}

DustResultType DplStlLogicSelect::DustActionExecute() {
	DustResultType ret = optGetChildResult(DUST_RESULT_REJECT);

	if (DUST_RESULT_REJECT == ret) {
		DustRef ctx(DUST_CTX_SELF);
		unsigned int count = DustData::getMemberCount(ctx, DustRefCollectionMembers);

		if (pos < count) {
			DustEntity r = DustData::getRef(ctx, DustRefLinkTarget, pos++);
			requestRelay(r);
			ret = DUST_RESULT_READ;
		}
	}

	return ret;
}
