	sf::Texture player_ship;
    sf::Texture boss_ship;
    if (!player_ship.loadFromFile("res/Player Ship Pixel.png"))
        std::cerr << "Failed to load \"player_ship_alpha.png\"" << std::endl;
    if (!boss_ship.loadFromFile("res/Boss Ship MK I Pixeled.png"))
        std::cerr << "Failed to load \"Boss Framework.png\"" << std::endl;

    sf::Sprite player_sprite;
    sf::Sprite boss_sprite;

    player_sprite.setTexture(player_ship);
    player_sprite.setPosition(sf::Vector2f(protoLD.spawnX , protoLD.spawnY));
    float scaleFactor = 50.0f / player_ship.getSize().x;
    //player_sprite.setScale(scaleFactor, scaleFactor);   // Fixed width of 50; maintains original aspect ratio

    boss_sprite.setTexture(boss_ship);
    boss_sprite.setPosition(protoLD.flagShipX , protoLD.flagShipY);
    float bossScaleFactor = 140.0f / boss_ship.getSize().x;
    //boss_sprite.setScale(bossScaleFactor, bossScaleFactor);
    */
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            } else if (event.type == sf::Event::Resized) {
//                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
//                mainView.reset(visibleArea);
//            }
//        }
//
//        window.clear();
//        window.setView(mainView);
//        window.draw(player_sprite);
//        window.draw(boss_sprite);
//        window.setView(minimapView);
//        window.draw(player_sprite);
//        window.draw(boss_sprite);
//        window.display();