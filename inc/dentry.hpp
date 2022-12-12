#ifndef DENTRY__HPP
#define DENTRY__HPP

namespace aoc {
    namespace dentry {
        struct dentry;
        struct file;

        using dentry_p = dentry*;//std::shared_ptr<dentry>;
        using file_p = file*;//std::shared_ptr<file>;

        using var_t = std::variant<dentry_p, file_p>;
        using map_t = std::map<std::string, var_t>;

        /* if parent == nullptr, then root directory */
        struct dentry {
            dentry_p parent;

            dentry():parent(nullptr), size(0) {}
            dentry(dentry_p parent, std::string name):parent{parent}, size(0), name(name) {}

            map_t map;
            uint32_t size;
            std::string name; /* for debug */
        };

        /* NOTE: part 1 doesn't really need file entries */
        struct file {
            dentry_p parent;
            const uint32_t size;

            file(uint32_t size):parent(nullptr), size(size) {}
            file(dentry_p parent, uint32_t size):parent{parent}, size(size) {}
        };

        void parse_dentry(dentry_p root);
    }
}

#endif
