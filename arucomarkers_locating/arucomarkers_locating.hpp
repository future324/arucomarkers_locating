#include"aruco2d.hpp"
#define devView(i) imshow(#i,i);

class complexID
{
public:
	complexID() :cid_number(-1) {

	}
	complexID operator , (int id) {
		ids.push_back(id);
	}
	int operator [] (int i) {
		return ids[i];
	}
	bool operator == (complexID in) {
		auto size = in.size();
		if (size < ids.size()*0.8f) return false;
		auto thresh = in.size()*0.8f;
		int matched = 0;
		for (size_t i = 0; i < size; i++)
		{
			if (find(in[i])) matched += 1;
		}
		return matched >= thresh ? true : false;
	}
	void SetID(int id) {
		cid_number = id;
	}
	int QueryID() {
		return cid_number;
	}
	int size() {
		return ids.size();
	}
private:
	bool find(int id) {
		for (size_t i = 0; i < ids.size(); i++){
			if (id == ids[i]) return true;
		}
		return false;
	}
	vector<int> ids;
	int cid_number;
};

class arucoLocating : public aruco2d
{
public:
	void Init(cv::aruco::PREDEFINED_DICTIONARY_NAME dictName) {
		sidePixels = (200);
		borderBits = (1);
		parameters = (cv::aruco::DetectorParameters::create());
		dictionary = getPredefinedDictionary(dictName);
		dictionarySize = dictNameToSize(dictName);
	}
	void RegistlocatingID(int idNumber, complexID cid) {
		cid.SetID(idNumber);
		candidate_cids.push_back(cid);
	}
	complexID QueryDetectedIDs(cv::Mat &frame) {
		auto n_ids = detect(frame);
		auto marker_ids = QueryMarkerIds();
		complexID cId;
		for (size_t i = 0; i < n_ids; i++){
			cId, marker_ids[i];
		}
		return cId;
	}
	complexID QueryMatched(complexID cid) {
		for (size_t i = 0; i < candidate_cids.size(); i++)
		{
			if (candidate_cids[i] == cid) return candidate_cids[i];
		}
		return cid;
	}
private:
	vector<complexID> candidate_cids;
};
