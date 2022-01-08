#include "reconstruction_manager.h"


void reconstruction_manager::add_parameters(std::vector<std::string> *all_comands){

    std::vector<std::string>::iterator it = (*all_comands).begin();
    while(it != (*all_comands).end()){

        if(*it == "--image_path" || *it == "-image_path" || *it == "image_path"){
            it++;
            if(it != (*all_comands).end()){
                image_path = *it;
            }else break;
        }

        if(*it == "--full_reconstruct" || *it == "-full_reconstruct" || *it == "full_reconstruct"){
            full_reconstruct = true;
        }

        if(*it == "-recursive_image_fetch" || *it == "--recursive_image_fetch" || *it == "recursive_image_fetch"){
            recursive_path_image_fetch = true;
        }

        if(*it == "--image_format" || *it == "-image_format" || *it == "image_format"){
            it++;
            if(it != (*all_comands).end()){
                set_image_formats(*it);
            }
        }

        it++;
    }

    return;
}


void reconstruction_manager::set_image_formats(std::string &formats){
    image_type.clear();

    while(formats.size() > 0){
        int pos = formats.find("_");
        if(pos != std::string::npos){
            std::string test = formats.substr(0, pos).find('.') == std::string::npos ? "." + formats.substr(0, pos) : formats.substr(0, pos);
            image_type.push_back(formats.substr(0, pos).find('.') == std::string::npos ? "." + formats.substr(0, pos) : formats.substr(0, pos));
            formats = formats.substr(pos + 1);
        }else{
            image_type.push_back(formats.find('.') == std::string::npos ? "." + formats : formats);
            break;
        }
    }

    return;
}


bool reconstruction_manager::is_accepted_image_format(std::string path){

    int idx = path.rfind('.');
    if(idx != std::string::npos){
        return std::find(image_type.begin(), image_type.end(), path.substr(idx)) != image_type.end() ? true : false;
    }

    return false;
}


void reconstruction_manager::Find_image_paths(){

    std::vector<std::string> path_queue = {image_path};

    if(boost::filesystem::exists(image_path) && boost::filesystem::is_directory(image_path)){

        while(path_queue.size() > 0){
            boost::filesystem::path base_path{path_queue[0]};
            path_queue.erase(path_queue.begin());
            boost::filesystem::directory_iterator itr{base_path};
            boost::filesystem::directory_iterator end_itr;
            for(itr; itr != end_itr; ++itr){
                
                if(boost::filesystem::is_regular_file(itr->path())){
                    if(is_accepted_image_format(itr->path().string())) image_paths.push_back(itr->path().string());
                }

                if(boost::filesystem::is_directory(itr->path()) && recursive_path_image_fetch){
                    path_queue.push_back(itr->path().string());
                }
            }
        }
    }

    return;

}



void reconstruction_manager::ORB_extraction(){

    for(unsigned int i = 0; i < image_paths.size(); i++){
        images[i] = image(image_paths[i], i);
        images[i].extract_features();
    }

}

int make_idx(int image_id1, int image_id2){
    if(image_id1 > image_id2) return 2147483647 * image_id2 + image_id1;
    else return 2147483647 * image_id1 + image_id2;
}

void extract_image_pairs(int pair_id, int &image_id1, int &image_id2){
    image_id2 = pair_id % 2147483647;
    image_id1 = (pair_id - image_id2) / 2147483647;
    return;
}

void reconstruction_manager::Feature_matching(){

    for(int i = 0; i < images.size(); i++){
        for(int j = i; j < images.size(); j++){
            image_matches[make_idx(i, j)] = images[i].match_features(images[j]);
        }
    }

    return;
}

template<typename T>
std::vector<std::pair<T, T>> obtain_combinations(const std::vector<T>& v){
    
    std::vector<std::pair<T, T>> ret;

    for(int i = 0; i < v.size(); i++){
        for(int j = i; j < v.size(); j++){
            ret.push_back(std::make_pair(v[i], v[j]));
        }
    }
    return ret;
}


void reconstruction_manager::Image_reconstruction(){

    //Find first initial image pair

    std::vector<int> idx;

    for(auto it : images){
        idx.push_back(it.first);
    }

    std::vector<std::pair<int, int>> idx_pairs = obtain_combinations<int>(idx);

    for(int i = 0; i < idx_pairs.size(); i++){

        transform_ransac(image_matches[make_idx(idx_pairs[i].first, idx_pairs[i].second)]);
    }

    //Start adding the 
};


void reconstruction_manager::reconstruct_scene(){
    //First, get all the images in the folder
    //find_images_path
    //Secondly extract the ORB features and descriptors from all of them
    //extract images ORB
    //Start reconstruction process (find initial image pair, match with good homography and iteratively continue doing it)
    //Finish

    Find_image_paths();

    ORB_extraction();

    Feature_matching();

    Image_reconstruction();

}

