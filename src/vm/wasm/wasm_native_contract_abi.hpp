#pragma once
#include "wasm/abi_def.hpp"

namespace wasm {

    static inline abi_def wasmio_contract_abi() {

        abi_def wasmio_abi;

        if( wasmio_abi.version.size() == 0 ) {
            wasmio_abi.version = "wasm::abi/1.0";
        }

        wasmio_abi.structs.emplace_back(struct_def{
                "setcode", "", {
                        {"account", "name"},
                        {"code", "bytes"},
                        {"abi", "bytes"},
                        {"memo", "string"}
                }
        });

        wasmio_abi.structs.emplace_back(struct_def{
                "transfer", "", {
                        {"from", "name"},
                        {"to", "name"},
                        {"quantity", "asset"},
                        {"memo", "string"}
                }
        });

        wasmio_abi.actions.push_back(action_def{"setcode", "setcode", ""});
        wasmio_abi.actions.push_back(action_def{"transfer", "transfer", ""});

        return wasmio_abi;

    }


}