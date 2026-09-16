/* -------------------------------------------------------------------------
 * This file is part of the MindStudio project.
 * Copyright (c) 2025 Huawei Technologies Co.,Ltd.
 *
 * MindStudio is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 * ------------------------------------------------------------------------- */

#ifndef WORKLOAD_ANALYSIS_MSKPP_SINGLETON_H
#define WORKLOAD_ANALYSIS_MSKPP_SINGLETON_H

template <class T> class Singleton {
public:
    static T *instance() {
        static T value;
        return &value;
    }

    Singleton(Singleton const &) = delete; // copy ctor disabled
    Singleton &operator=(Singleton const &) = delete; // copy assign disabled
    Singleton(Singleton &&) = delete; // move ctor disabled
    Singleton &operator=(Singleton &&) = delete; // move assign disabled

protected:
    Singleton() = default; // ctor hidden
    virtual ~Singleton() = default; // dtor hidden
};

#endif // WORKLOAD_ANALYSIS_MSKPP_SINGLETON_H
