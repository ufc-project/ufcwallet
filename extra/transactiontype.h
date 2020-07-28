#ifndef TRANSACTIONTYPE_H
#define TRANSACTIONTYPE_H

// 不同类型交易对应的operation类型
#define TRANSACTION_TYPE_NORMAL                 0       // 普通交易
#define TRANSACTION_TYPE_REGISTER_ACCOUNT       5       // 注册账户
#define TRANSACTION_TYPE_UPDATE_ACCOUNT         6       // 更新账户信息（挖矿管理费）
#define TRANSACTION_TYPE_BIND_TUNNEL            10888      // 绑定tunnel地址
#define TRANSACTION_TYPE_UNBIND_TUNNEL          11888      // 解绑tunnel地址
#define TRANSACTION_TYPE_UPDATE_ASSET_PK        12888      // guard更新冷热钱包多签地址私钥
#define TRANSACTION_TYPE_ISSUE_ASSET            14      // 增发资产
#define TRANSACTION_TYPE_FEED_PRICE             20      // 喂价
#define TRANSACTION_TYPE_CREATE_MINER           21      // 成为citizen
#define TRANSACTION_TYPE_SPONSOR_PROPOSAL       23      // 发起提案
#define TRANSACTION_TYPE_PROPOSAL_APPROVE       24      // 提案投票
#define TRANSACTION_TYPE_CREATE_DIRECTOR           30      // 创建senator
#define TRANSACTION_TYPE_FORMAL_DIRECTOR           31      // 成为正式guard
#define TRANSACTION_TYPE_RESIGN_DIRECTOR           33      // 使guard辞职
#define TRANSACTION_TYPE_LOCKBALANCE            48      // 投票资产给miner
#define TRANSACTION_TYPE_FORECLOSE              49      // 赎回投票资产
#define TRANSACTION_TYPE_DIRECTOR_LOCK_BALANCE   50      // senator交保证金
#define TRANSACTION_TYPE_CANCEL_WITHDRAW        59888      // 取消提现
#define TRANSACTION_TYPE_DEPOSIT                60888      // 充值交易（多签转HX-BTC）
#define TRANSACTION_TYPE_WITHDRAW               61888      // 提现交易
#define TRANSACTION_TYPE_WITHDRAW_CROSSCHAIN    62888      // 取消提现
#define TRANSACTION_TYPE_WITHDRAW_SIGN          63888      // 提现交易签名
#define TRANSACTION_TYPE_WITHDRAW_FINAL         64888      // 提现交易final
#define TRANSACTION_TYPE_COLDHOT                66888      // 冷热钱包转账
#define TRANSACTION_TYPE_COLDHOT_CROSSCHAIN     67888
#define TRANSACTION_TYPE_COLDHOT_SIGN           68888      // 冷热钱包转账签名
#define TRANSACTION_TYPE_COLDHOT_FINAL          69888      // 冷热钱包转账final
#define TRANSACTION_TYPE_COLDHOT_CANCEL         72888      // guard取消冷热钱包互转提案
#define TRANSACTION_TYPE_MINE_INCOME            52      // 投票挖矿收入
#define TRANSACTION_TYPE_CHANGE_ASSET_ACCOUNT   74888      // 变更冷热钱包多签地址 （只在提案的子op中）
#define TRANSACTION_TYPE_CREATE_ASSET           53      // 发行资产
#define TRANSACTION_TYPE_CONTRACT_REGISTER      54      // 注册合约
#define TRANSACTION_TYPE_CONTRACT_INVOKE        57      // 调用合约
#define TRANSACTION_TYPE_CONTRACT_TRANSFER      59      // 转账到合约
#define TRANSACTION_TYPE_PROPOSAL_CONTRACT_TRANSFER_FEE  60      // 修改合约转出手续费提案
#define TRANSACTION_TYPE_CREATE_GUARANTEE       61      // 创建承兑单
#define TRANSACTION_TYPE_CANCEL_GUARANTEE       62      // 撤销承兑单
#define TRANSACTION_TYPE_WITHDRAW_CANCEL        85888      // guard取消提现提案
#define TRANSACTION_TYPE_SET_PUBLISHER          63      // 设置喂价人
#define TRANSACTION_TYPE_CROSSCHAIN_FEE         87888      // 设置跨链提现费用
#define TRANSACTION_TYPE_OBTAIN_BONUS           65      // 领取分红
#define TRANSACTION_TYPE_SET_LOCKBALANCE        66      // 设置senator的保证金
#define TRANSACTION_TYPE_SIGN_ETH_MULTI_CREATE  97888      // senator签名创建以太多签账户 senator_sign_eths_multi_account_create_trx
#define TRANSACTION_TYPE_SIGN_ETH_FINAL         98888      // senator签名以太交易 senator_sign_eths_final_trx
#define TRANSACTION_TYPE_SIGN_ETH_COLDHOT_FINAL 100888     // senator签名以太冷热钱包转账交易 senator_sign_eths_final_trx
#define TRANSACTION_TYPE_CITIZEN_PROPOSAL       101888     // citizen发起提案
#define TRANSACTION_TYPE_CITIZEN_CHANGE_DIRECTOR 102888     // citizen发起更换senator的提案
#define TRANSACTION_TYPE_BLACKLIST              71     // 黑名单提案
#define TRANSACTION_TYPE_PROPOSAL_CHANGE_GAS    115888     // 改变eth gas提案

#endif // TRANSACTIONTYPE_H
