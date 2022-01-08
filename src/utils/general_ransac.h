
template<class T, class U>
class general_ransac{

    public:

        general_ransac(){
            threshold = 0;
        }
        general_ransac(std::vector<std::pair<T, U>> data, int thresh = 0){
            for(int i = 0; i < data.size(); i++){
                input.push_back(data[i].first);
                output.push_back(data[i].second);
                threshold = thresh;
            }
        }

        general_ransac(std::vector<T> input_, std::vector<U> output_, int thresh = 0){
            input = input_;
            output = output_;
            threshold = thesh;
        }
    
    private:
        int threshold;
        int num_inliners;
        std::vector<T> input;
        std::vector<U> output;


};