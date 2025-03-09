#ifndef LIBOTOCURL_STORAGE_FILE_STORAGE_TEST_HPP
#define LIBOTOCURL_STORAGE_FILE_STORAGE_TEST_HPP

namespace otocurl::storage::unit_test {

    class FileStorageTest {

        public:
            void set_input_filesize_to_0();
            void set_input_filesize_to_1KB();         
            void set_input_filesize_to_2047MB();
            void set_input_filesize_to_2GB();
            void set_input_filesize_to_99TB();
            void set_input_filesize_to_n1KB();

    };

}

#endif