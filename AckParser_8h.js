var AckParser_8h =
[
    [ "__FragmentAckParser", "struct____FragmentAckParser.html", "struct____FragmentAckParser" ],
    [ "ACK_EVENT_TYPE_BUFFERING", "AckParser_8h.html#a4ce515ace76da791728722dc5219fbf0", null ],
    [ "ACK_EVENT_TYPE_ERROR", "AckParser_8h.html#a69d09f4e51cd80c02aeda9bb6e452d42", null ],
    [ "ACK_EVENT_TYPE_IDLE", "AckParser_8h.html#adf3dac89139b330b3451d18cc6630c52", null ],
    [ "ACK_EVENT_TYPE_PERSISTED", "AckParser_8h.html#a15403fb148a7a90eda6f29520cf482de", null ],
    [ "ACK_EVENT_TYPE_RECEIVED", "AckParser_8h.html#aed06bfe74e6a471da425c5a5739efe66", null ],
    [ "ACK_KEY_NAME_ERROR_ID", "AckParser_8h.html#a058dc329adf272c922701ff4ca51bd9b", null ],
    [ "ACK_KEY_NAME_EVENT_TYPE", "AckParser_8h.html#a18a2497183e3c10f58e59f4124e2b21d", null ],
    [ "ACK_KEY_NAME_FRAGMENT_NUMBER", "AckParser_8h.html#a095fb745f5c061cf79b040ff409d8b24", null ],
    [ "ACK_KEY_NAME_FRAGMENT_TIMECODE", "AckParser_8h.html#a7f4b99faba6575bf80bc544d06e72254", null ],
    [ "ACK_PARSER_CLOSE_BRACE", "AckParser_8h.html#afcfe74e6213924fe470dde3d98494789", null ],
    [ "ACK_PARSER_CLOSE_BRACKET", "AckParser_8h.html#a6a6e6bb6cc1c7a8f5fd83dd9f1d75e1d", null ],
    [ "ACK_PARSER_COMMA", "AckParser_8h.html#a91d97028f97bca1130ac8d4d5b40bc45", null ],
    [ "ACK_PARSER_DELIMITER", "AckParser_8h.html#a8c7947eced5ddac5a54b7133f96e4387", null ],
    [ "ACK_PARSER_OPEN_BRACE", "AckParser_8h.html#a983253b2a709098d42cc713481232e59", null ],
    [ "ACK_PARSER_OPEN_BRACKET", "AckParser_8h.html#a3a8a6932002a5f4e7834681ac8d26486", null ],
    [ "ACK_PARSER_QUOTE", "AckParser_8h.html#aa83cad6533f8c50a041711f63c0b9b82", null ],
    [ "IS_ACK_START_OF_NUMERIC_VALUE", "AckParser_8h.html#a8f94c35962aa0c11f4be1eb550078efc", null ],
    [ "FragmentAckParser", "AckParser_8h.html#adae87797feaecf563f5f1ec72763cdad", null ],
    [ "PFragmentAckParser", "AckParser_8h.html#aec3d7923a3ae8635821247ad79bdb595", null ],
    [ "FRAGMENT_ACK_KEY_NAME", "AckParser_8h.html#a2f91a504cd945596e52006556ec2718f", [
      [ "FRAGMENT_ACK_KEY_NAME_EVENT_TYPE", "AckParser_8h.html#a2f91a504cd945596e52006556ec2718fa1a46e5a30d66d0fcbaf93d92461ad680", null ],
      [ "FRAGMENT_ACK_KEY_NAME_FRAGMENT_NUMBER", "AckParser_8h.html#a2f91a504cd945596e52006556ec2718fa0e38d4e7de6da36f65c2647134334b55", null ],
      [ "FRAGMENT_ACK_KEY_NAME_FRAGMENT_TIMECODE", "AckParser_8h.html#a2f91a504cd945596e52006556ec2718fafc7564fff30d32a0497e1a5fe20eee1f", null ],
      [ "FRAGMENT_ACK_KEY_NAME_ERROR_ID", "AckParser_8h.html#a2f91a504cd945596e52006556ec2718fa158a8f91460c7db8bde4f89ebea998c5", null ],
      [ "FRAGMENT_ACK_KEY_NAME_UNKNOWN", "AckParser_8h.html#a2f91a504cd945596e52006556ec2718faac2662f6e53cbd69b1fcf19ee454bae4", null ],
      [ "FRAGMENT_ACK_KEY_NAME_MAX", "AckParser_8h.html#a2f91a504cd945596e52006556ec2718faeb93817c975023f070fc4789f63195ff", null ]
    ] ],
    [ "FRAGMENT_ACK_PARSER_STATE", "AckParser_8h.html#abf5dfc9c3a3a08c702e71f9a51798d81", [
      [ "FRAGMENT_ACK_PARSER_STATE_START", "AckParser_8h.html#abf5dfc9c3a3a08c702e71f9a51798d81a89ade7f9f40abfb1d601c2ba930cf1f5", null ],
      [ "FRAGMENT_ACK_PARSER_STATE_ACK_START", "AckParser_8h.html#abf5dfc9c3a3a08c702e71f9a51798d81a759d25ef9ac074db2fd941913c433a3a", null ],
      [ "FRAGMENT_ACK_PARSER_STATE_KEY_START", "AckParser_8h.html#abf5dfc9c3a3a08c702e71f9a51798d81afa4a8bb244d6515d8766fd570ea3c3b9", null ],
      [ "FRAGMENT_ACK_PARSER_STATE_DELIMITER", "AckParser_8h.html#abf5dfc9c3a3a08c702e71f9a51798d81ad5d31092cc79cf18bab7790c05b30a18", null ],
      [ "FRAGMENT_ACK_PARSER_STATE_BODY_START", "AckParser_8h.html#abf5dfc9c3a3a08c702e71f9a51798d81a94859bb4577b1378b89bbb11b72cd399", null ],
      [ "FRAGMENT_ACK_PARSER_STATE_SKIP_BODY_BRACE_END", "AckParser_8h.html#abf5dfc9c3a3a08c702e71f9a51798d81a01ab81dd074a5fa2e9495f186e397dfb", null ],
      [ "FRAGMENT_ACK_PARSER_STATE_SKIP_BODY_BRACKET_END", "AckParser_8h.html#abf5dfc9c3a3a08c702e71f9a51798d81a079e7410107eb4dc54ff39dd20f379b8", null ],
      [ "FRAGMENT_ACK_PARSER_STATE_TEXT_VALUE", "AckParser_8h.html#abf5dfc9c3a3a08c702e71f9a51798d81ace9f441b815a7e9f3fe094a87a7d1d9f", null ],
      [ "FRAGMENT_ACK_PARSER_STATE_NUMERIC_VALUE", "AckParser_8h.html#abf5dfc9c3a3a08c702e71f9a51798d81a3b39959a4268b071864aceb47afce68d", null ],
      [ "FRAGMENT_ACK_PARSER_STATE_VALUE_END", "AckParser_8h.html#abf5dfc9c3a3a08c702e71f9a51798d81af0d827a2a75bd9c923c88cf7e09539ce", null ]
    ] ],
    [ "getAckErrorTypeFromErrorId", "AckParser_8h.html#a48dc2353999d0ec8507eb02e5bd5acae", null ],
    [ "getFragmentAckKeyName", "AckParser_8h.html#a92faa8797c72a4251d6ec67f90cb2f79", null ],
    [ "getFragmentAckType", "AckParser_8h.html#a632dec27d9b90b6a5eeea84002bc7750", null ],
    [ "parseFragmentAck", "AckParser_8h.html#abdb2097ec2155d7be6e207eff6ab3d57", null ],
    [ "processAckValue", "AckParser_8h.html#a9a86027096624e28a80337aa96cea677", null ],
    [ "processParsedAck", "AckParser_8h.html#af3fd636d5b4dad5f5a609057a8cdf844", null ],
    [ "resetAckParserState", "AckParser_8h.html#aa01572f3b09b4d0e5ac2ccba6f1fa30a", null ],
    [ "validateParsedAck", "AckParser_8h.html#a58c31e57b6f709c4a7f21c4320a7e32f", null ]
];